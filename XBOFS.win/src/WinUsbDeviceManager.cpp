#include "pch.h"
#include "XBOFS.win/WinUsbDeviceManager.h"
#include "XBOFS.win/utils.h"
#include <qabstracteventdispatcher.h>
#include <qeventloop.h>
#include <fmt/core.h>

using namespace XBOFSWin;
/*
Constructs the WinUsbDeviceManager and starts its event loop in a separate thread
*/
WinUsbDeviceManager::WinUsbDeviceManager(bool autoStartWinUsbDevices, std::shared_ptr<spdlog::logger> logger, QObject* parent)
: QObject(parent), logger(logger), autoStartWinUsbDevices(autoStartWinUsbDevices)
{}

void WinUsbDeviceManager::run() {        
    logger->info("Entered run()");        
    logger->info("Starting scan loop");
    while (!QThread::currentThread()->isInterruptionRequested()) {
        emit winUsbDeviceManagerScanning();        
        auto devicePaths = this->retrieveDevicePaths();        
        // Check the updated set for new devicePaths
        for (auto devicePath : devicePaths) {
            if (devicePathWinUsbDeviceMap.find(devicePath) != devicePathWinUsbDeviceMap.end()) continue;             
            this->logger->info(L"Adding WinUsbDevice at {}", devicePath);            
            auto winUsbDeviceThread = new QThread();            
            auto winUsbDeviceLoggerName = fmt::format(L"WinUsbDevice {}", devicePath);
            auto winUsbDeviceLogger = get_logger(winUsbDeviceLoggerName, logger->sinks());
            auto winUsbDevice = new WinUsbDevice(devicePath, winUsbDeviceLogger);
            connect(winUsbDeviceThread, &QThread::finished, winUsbDevice, &QObject::deleteLater);
            connect(winUsbDeviceThread, &QThread::started, winUsbDevice, &WinUsbDevice::run);
            winUsbDevice->moveToThread(winUsbDeviceThread);
            devicePathWinUsbDeviceMap.insert({ devicePath, std::make_pair(winUsbDeviceThread, winUsbDevice) });                        
            if (autoStartWinUsbDevices) winUsbDeviceThread->start();
            emit winUsbDeviceAdded(devicePath, winUsbDevice);
        }  
        // Check for WinUsbDevices to remove
        for (auto iterator = devicePathWinUsbDeviceMap.begin(); iterator != devicePathWinUsbDeviceMap.end(); )
        {            
            auto devicePath = iterator->first;            
            auto winUsbDeviceThread = iterator->second.first;
            auto winUsbDevice = iterator->second.second;
            if (devicePaths.find(devicePath) == devicePaths.end()) {
                logger->info(L"Requesting interruption of thread handling {}", devicePath);
                winUsbDeviceThread->requestInterruption();
                logger->info(L"Signalling thread handling {} to quit", devicePath);
                winUsbDeviceThread->quit();
                logger->info(L"Waiting for thread handling {} to quit", devicePath);                
                winUsbDeviceThread->wait();                
                emit winUsbDeviceRemoved(devicePath);
                delete winUsbDeviceThread;
                iterator = devicePathWinUsbDeviceMap.erase(iterator);
            }
            else ++iterator;
        }
        // Processes messages in thread message queue
        QThread::currentThread()->eventDispatcher()->processEvents(QEventLoop::AllEvents);
        if (!QThread::currentThread()->isInterruptionRequested())
        {
            logger->info("Sleeping for 1000 milliseconds");
            emit winUsbDeviceManagerSleeping();            
            QThread::msleep(1000);            
        }
        previousDevicePaths = devicePaths;
    }
    logger->info("Completed scan loop");    
    emit winUsbDeviceManagerTerminating();    
    // TODO: Duplicate code, we should remove it
    for (auto tuple : devicePathWinUsbDeviceMap) {
        auto devicePath = tuple.first;        
        auto winUsbDeviceThread = tuple.second.first;        
        logger->info(L"Requesting interruption of thread handling {}", devicePath);
        winUsbDeviceThread->requestInterruption();
        logger->info(L"Signalling thread handling {} to quit", devicePath);
        winUsbDeviceThread->quit();
        logger->info(L"Waiting for thread hanlding {} to quit", devicePath);
        winUsbDeviceThread->wait();        
        delete winUsbDeviceThread;
    }
    logger->info("Completed run()");
}

void WinUsbDeviceManager::startWinUsbDeviceThread(const std::wstring& devicePath) {
    auto iterator = devicePathWinUsbDeviceMap.find(devicePath);
    if (iterator != devicePathWinUsbDeviceMap.end()) {
        logger->info(L"Starting thread handling {}", devicePath);
        iterator->second.first->start(QThread::HighestPriority);
    }
    else {
        logger->error(L"Unable to locate thread handling {}", devicePath);
    }
}

/*
Retrieve a vector of TCHAR* representing device paths that the device manager will work with
*/
std::set<std::wstring> WinUsbDeviceManager::retrieveDevicePaths() {
    CONFIGRET               configurationManagerResult  = CR_SUCCESS;
    HRESULT                 resultHandle                = S_OK;
    PTSTR                   deviceInterfaceList         = NULL;
    ULONG                   deviceInterfaceListSize     = 0;    
    std::set<std::wstring>  newDevicePaths;
    //
    // Enumerate all devices exposing the interface. Do this in a loop
    // in case a new interface is discovered while this code is executing,
    // causing CM_Get_Device_Interface_List to return CR_BUFFER_SMALL.
    //
    logger->debug("Retrieving device interface paths");
    do {        
        configurationManagerResult = CM_Get_Device_Interface_List_Size(&deviceInterfaceListSize,
            (LPGUID)&GUID_DEVINTERFACE_XBOFS_WIN_CONTROLLER,
            NULL,
            CM_GET_DEVICE_INTERFACE_LIST_PRESENT);              

        if (configurationManagerResult != CR_SUCCESS) {
            resultHandle = HRESULT_FROM_WIN32(CM_MapCrToWin32Err(configurationManagerResult, ERROR_INVALID_DATA));
            break;
        }              

        logger->debug("Device interface list size in bytes: {}", deviceInterfaceListSize * sizeof(TCHAR));

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
    if (resultHandle != S_OK || (*deviceInterfaceList) == _T('\0')) {
        // TODO: Log error?        
    }
    else {        
        auto deviceInterfaceListMarker = deviceInterfaceList;
        auto position = 0;
        while (position < deviceInterfaceListSize) {
            auto devicePath = std::wstring(deviceInterfaceListMarker);
            auto devicePathSize = devicePath.size();
            if (!devicePathSize) break;            
            newDevicePaths.insert(devicePath);
            deviceInterfaceListMarker += devicePathSize + 1;
            position += devicePathSize + 1;
            logger->debug(L"Device interface path detected: {}", devicePath);
        }
        deviceInterfaceListMarker = NULL;
        logger->debug("{} device interfaces detected", newDevicePaths.size());        
    }    
    HeapFree(GetProcessHeap(), 0, deviceInterfaceList);
    return newDevicePaths;
}