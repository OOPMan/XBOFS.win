#include "WinUsbDeviceManager.h"

WinUsbDeviceManager::WinUsbDeviceManager()
{    
}


WinUsbDeviceManager::~WinUsbDeviceManager()
{
    for (auto tuple : this->devicePathWinUsbDeviceMap) delete tuple.second;            
    this->devicePathWinUsbDeviceMap.clear();
}

DWORD WINAPI WinUsbDeviceManager::staticRunEventLoop(void * winUsbDeviceManagerInstance) {
    WinUsbDeviceManager* winUsbDeviceManager = (WinUsbDeviceManager*)winUsbDeviceManagerInstance;
    return winUsbDeviceManager->runEventLoop();
}

DWORD WinUsbDeviceManager::runEventLoop(void) {    
    this->logger->info("Started event loop for WinUsbDeviceManager");
    this->runEventLoopFlag.test_and_set();
    while (this->runEventLoopFlag.test_and_set()) {        
        auto devicePaths = this->retrieveDevicePaths();        
        // Check the updated set for new devicePaths
        for (auto devicePath : devicePaths) {
            if (this->devicePathWinUsbDeviceMap.find(devicePath) != this->devicePathWinUsbDeviceMap.end()) continue;            
            this->logger->info("Adding WinUsbDevice at %v", devicePath);                      
            auto winUsbDevice = new WinUsbDevice(devicePath);
            this->devicePathWinUsbDeviceMap.insert({ devicePath, winUsbDevice });                        
        }  
        // Check for WinUsbDevices to remove
        for (auto tuple : this->devicePathWinUsbDeviceMap) {
            if (devicePaths.find(tuple.first) != devicePaths.end()) continue;
            delete tuple.second;
            this->devicePathWinUsbDeviceMap.erase(tuple.first);
        }        
        Sleep(1000);
    }
    this->logger->info("Completed event loop for WinUsbDeviceManager");
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
std::set<tstring> WinUsbDeviceManager::retrieveDevicePaths() {
    CONFIGRET           configurationManagerResult  = CR_SUCCESS;
    HRESULT             resultHandle                = S_OK;
    PTSTR               deviceInterfaceList         = NULL;
    ULONG               deviceInterfaceListSize     = 0;    
    std::set<tstring>   newDevicePaths;
    //
    // Enumerate all devices exposing the interface. Do this in a loop
    // in case a new interface is discovered while this code is executing,
    // causing CM_Get_Device_Interface_List to return CR_BUFFER_SMALL.
    //
    this->logger->debug("Retrieving device interface paths");
    do {        
        configurationManagerResult = CM_Get_Device_Interface_List_Size(&deviceInterfaceListSize,
            (LPGUID)&GUID_DEVINTERFACE_RazorAtroxWinUSBVigEmFeeder,
            NULL,
            CM_GET_DEVICE_INTERFACE_LIST_PRESENT);              

        if (configurationManagerResult != CR_SUCCESS) {
            resultHandle = HRESULT_FROM_WIN32(CM_MapCrToWin32Err(configurationManagerResult, ERROR_INVALID_DATA));
            break;
        }              

        this->logger->debug("Device interface list size in bytes: %v", deviceInterfaceListSize * sizeof(TCHAR));

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
            auto devicePath = tstring(deviceInterfaceListMarker);
            auto devicePathSize = devicePath.size();
            if (!devicePathSize) break;            
            newDevicePaths.insert(devicePath);
            deviceInterfaceListMarker += devicePathSize + 1;
            position += devicePathSize + 1;
            this->logger->debug("Device interface path detected: %v", devicePath);
        }
        deviceInterfaceListMarker = NULL;
        this->logger->debug("%v device interfaces detected", newDevicePaths.size());        
    }    
    HeapFree(GetProcessHeap(), 0, deviceInterfaceList);
    return newDevicePaths;
}