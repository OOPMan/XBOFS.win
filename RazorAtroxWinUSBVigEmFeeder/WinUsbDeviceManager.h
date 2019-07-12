#pragma once
#include "pch.h"
#include "WinUsbDevice.h"
#include "easylogging++.h"

#include <unordered_map>
#include <string>
#include <set>

/*

*/
class WinUsbDeviceManager
{
public:
    WinUsbDeviceManager();
    ~WinUsbDeviceManager();    

    static DWORD WINAPI staticRunEventLoop(void* Param);
    DWORD getThreadId();
    DWORD runEventLoop(void);
    HANDLE runEventLoopInThread();
protected:
    DWORD threadId;
    el::Logger* logger = el::Loggers::getLogger("WinUsbDeviceManager");
    std::set<TCHAR*> devicePaths;
    std::unordered_map<TCHAR*, WinUsbDevice*> devicePathWinUsbDeviceMap;
    std::unordered_map<TCHAR*, HANDLE> devicePathHandleMap;

    std::set<TCHAR*> retrieveDevicePaths();
private:
};

