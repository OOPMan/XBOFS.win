#pragma once
#include "pch.h"
#include "WinUsbDevice.h"

#include <cfgmgr32.h>

/*

*/
class WinUsbDeviceManager
{
public:    
    WinUsbDeviceManager(DWORD parentThreadId, DWORD uiManagerThreadId);
    ~WinUsbDeviceManager();    

    DWORD getThreadId();
    static DWORD WINAPI staticRunEventLoop(void* Param);    
    DWORD runEventLoop(void);    

protected:
    std::atomic_flag runEventLoopFlag           = ATOMIC_FLAG_INIT;
    DWORD parentThreadId                        = 0;
    DWORD uiManagerThreadId                     = 0;
    DWORD threadId                              = 0;
    HANDLE threadHandle                         = NULL;
    el::Logger* logger                          = el::Loggers::getLogger("WinUsbDeviceManager");    
    std::unordered_map<tstring, WinUsbDevice*> devicePathWinUsbDeviceMap;    

    std::set<tstring> retrieveDevicePaths();
private:
};

