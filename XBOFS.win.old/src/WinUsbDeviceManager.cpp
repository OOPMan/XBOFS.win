#include "XBOFS.win\WinUsbDeviceManager.h"
#include "XBOFS.win\utils.h";

using namespace XBOFSWin;
/*
Constructs the WinUsbDeviceManager and starts its event loop in a separate thread
*/
WinUsbDeviceManager::WinUsbDeviceManager(std::shared_ptr<spdlog::logger> logger, DWORD parentThreadId, DWORD uiManagerThreadId)
: Thread("WinUsbDeviceManager", logger, parentThreadId, uiManagerThreadId)
{}

DWORD WinUsbDeviceManager::run() {    
    this->notifyUIManager(RAWUVEF_WIN_USB_DEVICE_MANAGER_STARTED, NULL);
    this->logger->info("Started thread for {}", this->identifier);
    MSG threadMessage;
    bool loop = true;
    std::unordered_map<tstring, WinUsbDevice*> devicePathWinUsbDeviceMap;    
    this->logger->info("Starting scan loop for {}", this->identifier);
    while (loop) {
        this->notifyUIManager(RAWUVEF_WIN_USB_DEVICE_MANAGER_SCANNING, NULL);
        auto devicePaths = this->retrieveDevicePaths();        
        // Check the updated set for new devicePaths
        for (auto devicePath : devicePaths) {
            if (devicePathWinUsbDeviceMap.find(devicePath) != devicePathWinUsbDeviceMap.end()) continue;            
            this->logger->info("Adding WinUsbDevice at {}", utf8_encode(devicePath));
            #ifdef UNICODE
            auto identifier = utf8_encode(devicePath);
            #else
            auto identifier = devicePath;
            #endif // UNICODE                         
            auto winUsbDeviceLogger = setup_logger("WinUsbDevice", "", this->logger->sinks());
            auto winUsbDevice = new WinUsbDevice(devicePath, identifier, winUsbDeviceLogger, this->threadId, this->uiManagerThreadId);
            devicePathWinUsbDeviceMap.insert({ devicePath, winUsbDevice });                        
        }  
        // Check for WinUsbDevices to remove
        for (auto tuple : devicePathWinUsbDeviceMap) {
            if (devicePaths.find(tuple.first) != devicePaths.end()) continue;
            delete tuple.second;
            devicePathWinUsbDeviceMap.erase(tuple.first);
        }     
        // TODO: Processes messages in thread message queue
        if (PeekMessage(&threadMessage, NULL, WM_USER, WM_APP, PM_REMOVE) == TRUE && threadMessage.message == RAWUVEF_STOP) loop = false;
        else {
            this->notifyUIManager(RAWUVEF_WIN_USB_DEVICE_MANAGER_SLEEPING, NULL);
            Sleep(1000);
        }
    }
    this->logger->info("Completed scan loop for {}", this->identifier);    
    this->notifyUIManager(RAWUVEF_WIN_USB_DEVICE_MANAGER_TERMINATING, NULL);
    for (auto tuple : devicePathWinUsbDeviceMap) delete tuple.second;    
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
            (LPGUID)&GUID_DEVINTERFACE_XBOFS_WIN_CONTROLLER,
            NULL,
            CM_GET_DEVICE_INTERFACE_LIST_PRESENT);              

        if (configurationManagerResult != CR_SUCCESS) {
            resultHandle = HRESULT_FROM_WIN32(CM_MapCrToWin32Err(configurationManagerResult, ERROR_INVALID_DATA));
            break;
        }              

        this->logger->debug("Device interface list size in bytes: {}", deviceInterfaceListSize * sizeof(TCHAR));

        deviceInterfaceList = (PTSTR)HeapAlloc(GetProcessHeap(),
            HEAP_ZERO_MEMORY,
            deviceInterfaceListSize * sizeof(TCHAR));

        if (deviceInterfaceList == NULL) {
            resultHandle = E_OUTOFMEMORY;
            break;
        }

        configurationManagerResult = CM_Get_Device_Interface_List((LPGUID)&GUID_DEVINTERFACE_XBOFS_WIN_CONTROLLER,
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
            this->logger->debug("Device interface path detected: {}", utf8_encode(devicePath));
        }
        deviceInterfaceListMarker = NULL;
        this->logger->debug("{} device interfaces detected", newDevicePaths.size());        
    }    
    HeapFree(GetProcessHeap(), 0, deviceInterfaceList);
    return newDevicePaths;
}