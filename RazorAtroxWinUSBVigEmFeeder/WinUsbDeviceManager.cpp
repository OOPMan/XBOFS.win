#include "WinUsbDeviceManager.h"

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
    this->runEventLoopFlag.test_and_set();
    while (this->runEventLoopFlag.test_and_set()) {
        auto updatedDevicePaths = this->retrieveDevicePaths();
        // Check existing device paths to see if any paths were removed in the updated set
        //for (auto devicePath : this->devicePaths) {            
        //for (auto iterator = this->devicePaths
        //    if (updatedDevicePaths.find(devicePath) != updatedDevicePaths.end()) continue; 
        //    if (this->devicePathHandleMap.find(devicePath) != this->devicePathHandleMap.end()) continue;
        //    // TODO: Handle devicePath removed scenario            
        //}
        // Check the updated set for new devicePaths
        for (auto devicePath : updatedDevicePaths) {
            if (this->devicePathWinUsbDeviceMap.find(devicePath) != this->devicePathWinUsbDeviceMap.end()) continue;            
            this->logger->info("Adding WinUsbDevice at %s", devicePath);
            std::pair<WinUsbDevice*, HANDLE> test;
            test.first = new WinUsbDevice(devicePath);
            auto winUsbDevice = new WinUsbDevice(devicePath);
            this->devicePathWinUsbDeviceMap.insert({ devicePath, winUsbDevice });            
            auto threadHandle = winUsbDevice->runEventLoopInThread();
        }       
        // Check for closed thread handles
        /*for (auto pair : this->devicePathHandleMap) {
            if (WaitForSingleObject(pair.second, 0) == WAIT_OBJECT_0) {
                if (!CloseHandle(pair.second)) this->logger->info("Failed to close handle for %s", pair.first);
                else {
                    this->devicePathHandleMap.erase(pair.first);
                    if (this->devicePathWinUsbDeviceMap.find(pair.first) != this->devicePathWinUsbDeviceMap)
                }
            }
        }*/
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
    ULONG               deviceInterfaceListSize = 0;    
    std::set<TCHAR*>    newDevicePaths;
    //
    // Enumerate all devices exposing the interface. Do this in a loop
    // in case a new interface is discovered while this code is executing,
    // causing CM_Get_Device_Interface_List to return CR_BUFFER_SMALL.
    //
    do {
        configurationManagerResult = CM_Get_Device_Interface_List_Size(&deviceInterfaceListSize,
            (LPGUID)&GUID_DEVINTERFACE_RazorAtroxWinUSBVigEmFeeder,
            NULL,
            CM_GET_DEVICE_INTERFACE_LIST_PRESENT);              

        if (configurationManagerResult != CR_SUCCESS) {
            resultHandle = HRESULT_FROM_WIN32(CM_MapCrToWin32Err(configurationManagerResult, ERROR_INVALID_DATA));
            break;
        }              

        this->logger->info("Device interface list size in bytes: %d", deviceInterfaceListSize * sizeof(TCHAR));

        deviceInterfaceList = (PTSTR)HeapAlloc(GetProcessHeap(),
            HEAP_ZERO_MEMORY,
            deviceInterfaceListSize * sizeof(TCHAR));

        if (deviceInterfaceList == NULL) {
            resultHandle = E_OUTOFMEMORY;
            break;
        }

        configurationManagerResult = CM_Get_Device_Interface_List((LPGUID)&GUID_DEVINTERFACE_RazorAtroxWinUSBVigEmFeeder,
            NULL,
            deviceInterfaceList,
            deviceInterfaceListSize,
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
        auto deviceInterfaceListMarker = deviceInterfaceList;
        auto position = 0;
        while (position < deviceInterfaceListSize) {
            auto devicePath = std::basic_string<TCHAR>(deviceInterfaceListMarker);
            auto devicePathSize = devicePath.size();
            newDevicePaths.insert((TCHAR*)devicePath.c_str());
            deviceInterfaceListMarker += devicePathSize + 1;
            position += devicePathSize + 1;
            this->logger->info("New device path detected: %s", devicePath);
        }
        deviceInterfaceListMarker = NULL;
        this->logger->info("%d device interfaces detected", newDevicePaths.size());        
    }    
    HeapFree(GetProcessHeap(), 0, deviceInterfaceList);
    return newDevicePaths;
}