#pragma once
#include <unordered_map>
#include <string>
#include <set>
#include <atomic>

#include "pch.h"
#include "easylogging++.h"


/*
*/
class WinUsbDevice
{
public:
    std::atomic_flag runEventLoopFlag = ATOMIC_FLAG_INIT;

    WinUsbDevice(TCHAR* devicePath);
    ~WinUsbDevice();

    static DWORD WINAPI staticRunEventLoop(void* Param);
    DWORD getThreadId();
    DWORD runEventLoop(void);
    HANDLE runEventLoopInThread();
protected:
    TCHAR* devicePath;
    DWORD threadId;
    el::Logger* logger = el::Loggers::getLogger("WinUsbDevice");
private:
};

