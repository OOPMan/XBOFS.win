#include "WinUsbDeviceManager.h"

/*
Constructs the WinUsbDeviceManager and starts its event loop in a separate thread
*/
WinUsbDeviceManager::WinUsbDeviceManager(DWORD parentThreadId, DWORD uiManagerThreadId)
{    
    this->parentThreadId = parentThreadId;
    this->uiManagerThreadId = uiManagerThreadId;
    this->logger->info("Starting event loop for WinUsbDeviceManager");
    this->threadHandle = CreateThread(NULL, 0, staticRunEventLoop, (void*)this, 0, &this->threadId);
}

WinUsbDeviceManager::~WinUsbDeviceManager()
{
    // TODO: This is not working properly when exiting the software
    this->logger->info("Terminating event loop for WinUsbDeviceManager");   
    for (auto tuple : this->devicePathWinUsbDeviceMap) delete tuple.second;            
    this->devicePathWinUsbDeviceMap.clear();      
    this->runEventLoopFlag.clear();
    while (WaitForSingleObject(this->threadHandle, 10) != WAIT_OBJECT_0) {};
    CloseHandle(this->threadHandle);
    this->logger->info("Terminated event loop for WinUsbDeviceManager");
}

DWORD WinUsbDeviceManager::getThreadId() {
    return this->threadId;
}

DWORD WINAPI WinUsbDeviceManager::staticRunEventLoop(void * winUsbDeviceManagerInstance) {    
    WinUsbDeviceManager* winUsbDeviceManager = (WinUsbDeviceManager*)winUsbDeviceManagerInstance;
    return winUsbDeviceManager->runEventLoop();
}

DWORD WinUsbDeviceManager::runEventLoop(void) {    
    MSG threadMessage;
    PeekMessage(&threadMessage, NULL, WM_USER, WM_USER, PM_NOREMOVE);
    this->logger->info("Started event loop for WinUsbDeviceManager");
    this->runEventLoopFlag.test_and_set();
    while (this->runEventLoopFlag.test_and_set()) {        
        auto devicePaths = this->retrieveDevicePaths();        
        // Check the updated set for new devicePaths
        for (auto devicePath : devicePaths) {
            if (this->devicePathWinUsbDeviceMap.find(devicePath) != this->devicePathWinUsbDeviceMap.end()) continue;            
            this->logger->info("Adding WinUsbDevice at %v", devicePath);                      
            auto winUsbDevice = new WinUsbDevice(devicePath, this->threadId, this->uiManagerThreadId);
            this->devicePathWinUsbDeviceMap.insert({ devicePath, winUsbDevice });                        
        }  
        // Check for WinUsbDevices to remove
        for (auto tuple : this->devicePathWinUsbDeviceMap) {
            if (devicePaths.find(tuple.first) != devicePaths.end()) continue;
            delete tuple.second;
            this->devicePathWinUsbDeviceMap.erase(tuple.first);
        }     
        // TODO: Processes messages in thread message queue
        Sleep(1000);
    }
    this->logger->info("Completed event loop for WinUsbDeviceManager");
    return 0;
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