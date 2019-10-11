#include "XBOFS.win\WinUsbDeviceManager.h"
#include "XBOFS.win\utils.h";
#include <qabstracteventdispatcher.h>
#include <qeventloop.h>

using namespace XBOFSWin;
/*
Constructs the WinUsbDeviceManager and starts its event loop in a separate thread
*/
WinUsbDeviceManager::WinUsbDeviceManager(std::string identifier, std::shared_ptr<spdlog::logger> logger)
: QObject(), identifier(identifier), logger(logger)
{}

void WinUsbDeviceManager::run() {        
    this->logger->info("Started thread for {}", this->identifier);
    MSG threadMessage;
    bool loop = true;
      
    this->logger->info("Starting scan loop for {}", this->identifier);
    while (loop && !QThread::currentThread()->isInterruptionRequested()) {
        emit winUsbDeviceManagerScanning();        
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
            auto winUsbDeviceThread = new QThread();
            auto winUsbDeviceLogger = setup_logger("WinUsbDevice", "", this->logger->sinks());
            auto winUsbDevice = new WinUsbDevice(devicePath, identifier, winUsbDeviceLogger);
            connect(winUsbDeviceThread, &QThread::finished, winUsbDevice, &QObject::deleteLater);
            connect(winUsbDeviceThread, &QThread::started, winUsbDevice, &WinUsbDevice::run);
            winUsbDevice->moveToThread(winUsbDeviceThread);
            devicePathWinUsbDeviceMap.insert({ devicePath, std::make_pair(winUsbDeviceThread, winUsbDevice) });                        
            winUsbDeviceThread->start();
        }  
        // Check for WinUsbDevices to remove
        for (auto tuple : devicePathWinUsbDeviceMap) {
            if (devicePaths.find(tuple.first) != devicePaths.end()) continue;
            tuple.second.first->requestInterruption();
            tuple.second.first->terminate();
            tuple.second.first->wait();            
            devicePathWinUsbDeviceMap.erase(tuple.first);
        }     
        // Processes messages in thread message queue
        QThread::currentThread()->eventDispatcher()->processEvents(QEventLoop::AllEvents);
        if (QThread::currentThread()->isInterruptionRequested()) loop = false;        
        else {
            emit winUsbDeviceManagerSleeping();            
            QThread::msleep(1000);            
        }
    }
    this->logger->info("Completed scan loop for {}", this->identifier);    
    emit winUsbDeviceManagerTerminating();    
    for (auto tuple : devicePathWinUsbDeviceMap) {
        delete tuple.second.second;
        delete tuple.second.first;
    }
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