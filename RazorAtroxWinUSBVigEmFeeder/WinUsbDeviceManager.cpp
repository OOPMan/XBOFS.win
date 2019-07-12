#include "WinUsbDeviceManager.h"


#include <cfgmgr32.h>
#include <string.h>


WinUsbDeviceManager::WinUsbDeviceManager()
{    
}


WinUsbDeviceManager::~WinUsbDeviceManager()
{
}

DWORD WINAPI WinUsbDeviceManager::staticRunEventLoop(void * winUsbDeviceManagerInstance) {
    WinUsbDeviceManager* winUsbDeviceManager = (WinUsbDeviceManager*)winUsbDeviceManagerInstance;
    return winUsbDeviceManager->runEventLoop();
}

DWORD WinUsbDeviceManager::runEventLoop(void) {
    // TODO: Check condition should allow some way to break out
    while (true) {
        auto updatedDevicePaths = this->retrieveDevicePaths();
        // Check existing device paths to see if any paths were removed in the updated set
        for (auto devicePath : this->devicePaths) {            
            if (updatedDevicePaths.find(devicePath) != updatedDevicePaths.end()) continue; 
            // TODO: Handle devicePath removed scenario            
        }
        // Check the updated set for new devicePaths
        for (auto devicePath : updatedDevicePaths) {
            if (this->devicePathWinUsbDeviceMap.find(devicePath) != this->devicePathWinUsbDeviceMap.end()) continue;            
            auto winUsbDevice = new WinUsbDevice(devicePath);
            this->devicePathWinUsbDeviceMap.insert({ devicePath, winUsbDevice });
            auto threadHandle = winUsbDevice->runEventLoopInThread();
            this->devicePathHandleMap.insert({ devicePath, threadHandle });            
        }       
        this->devicePaths = updatedDevicePaths;
        Sleep(1000);
    }
    return 0;
}

DWORD WinUsbDeviceManager::getThreadId() {
    return this->threadId;
}

/*
*/
HANDLE WinUsbDeviceManager::runEventLoopInThread() {    
    return CreateThread(NULL, 0, staticRunEventLoop, (void*)this, 0, &this->threadId);
}

/*
Retrieve a vector of TCHAR* representing device paths that the device manager will work with
*/
std::set<TCHAR*> WinUsbDeviceManager::retrieveDevicePaths() {
    CONFIGRET           configurationManagerResult = CR_SUCCESS;
    HRESULT             resultHandle = S_OK;
    PTSTR               deviceInterfaceList = NULL;
    ULONG               deviceInterfaceListLength = 0;    
    std::set<TCHAR*>    devicePaths;
    //
    // Enumerate all devices exposing the interface. Do this in a loop
    // in case a new interface is discovered while this code is executing,
    // causing CM_Get_Device_Interface_List to return CR_BUFFER_SMALL.
    //
    do {
        configurationManagerResult = CM_Get_Device_Interface_List_Size(&deviceInterfaceListLength,
            (LPGUID)&GUID_DEVINTERFACE_RazorAtroxWinUSBVigEmFeeder,
            NULL,
            CM_GET_DEVICE_INTERFACE_LIST_PRESENT);
        this->logger->debug("Device interface list length: %d", deviceInterfaceListLength);

        if (configurationManagerResult != CR_SUCCESS) {
            resultHandle = HRESULT_FROM_WIN32(CM_MapCrToWin32Err(configurationManagerResult, ERROR_INVALID_DATA));
            break;
        }              
        
        deviceInterfaceList = (PTSTR)HeapAlloc(GetProcessHeap(),
            HEAP_ZERO_MEMORY,
            deviceInterfaceListLength * sizeof(TCHAR));

        if (deviceInterfaceList == NULL) {
            resultHandle = E_OUTOFMEMORY;
            break;
        }

        configurationManagerResult = CM_Get_Device_Interface_List((LPGUID)&GUID_DEVINTERFACE_RazorAtroxWinUSBVigEmFeeder,
            NULL,
            deviceInterfaceList,
            deviceInterfaceListLength,
            CM_GET_DEVICE_INTERFACE_LIST_PRESENT);

        if (configurationManagerResult != CR_SUCCESS) {            
            if (configurationManagerResult != CR_BUFFER_SMALL) {
                resultHandle = HRESULT_FROM_WIN32(CM_MapCrToWin32Err(configurationManagerResult, ERROR_INVALID_DATA));
            }
        }
    } while (configurationManagerResult == CR_BUFFER_SMALL);
    // Handle errors
    if (resultHandle != S_OK || deviceInterfaceList == TEXT('\0')) {
        // TODO: Log error
    }
    else {
        // Transform deviceInterfaceList to a vector
        TCHAR *next_token = NULL;
        TCHAR *token = NULL;
        const TCHAR separator = TEXT('\0');
        token = _tcstok_s(deviceInterfaceList, separator, &next_token);
        while (token != NULL) {
            // TODO: Add to vector
            devicePaths.insert(token);            
            token = _tcstok_s(deviceInterfaceList, separator, &next_token);

        }
        this->logger->debug("%d device interfaces detected", devicePaths.size());
    }    
    HeapFree(GetProcessHeap(), 0, deviceInterfaceList);
    return devicePaths;
}