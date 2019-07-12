#pragma once
#include "pch.h"
#include "easylogging++.h"

#include <unordered_map>
#include <string>
#include <set>

/*
*/
class WinUsbDevice
{
public:
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

