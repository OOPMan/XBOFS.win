#pragma once
#include "pch.h"
#include "WinUsbDevice.h"

#include <cfgmgr32.h>

struct WinUsbDeviceData {
    WinUsbDevice* winUsbDevice;
    HANDLE winUsbDeviceHandle;
};

/*

*/
class WinUsbDeviceManager
{
public:
    std::atomic_flag runEventLoopFlag = ATOMIC_FLAG_INIT;

    WinUsbDeviceManager();
    ~WinUsbDeviceManager();    

    static DWORD WINAPI staticRunEventLoop(void* Param);
    DWORD getThreadId();
    DWORD runEventLoop(void);
    HANDLE runEventLoopInThread();
protected:
    DWORD threadId;
    el::Logger* logger = el::Loggers::getLogger("WinUsbDeviceManager");    
    std::unordered_map<TCHAR*, WinUsbDevice*> devicePathWinUsbDeviceMap;    

    std::set<TCHAR*> retrieveDevicePaths();
private:
};

