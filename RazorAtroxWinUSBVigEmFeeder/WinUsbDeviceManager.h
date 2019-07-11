#pragma once
#include "pch.h"
#include "WinUsbDevice.h"
#include "easylogging++.h"

#include <unordered_map>
#include <vector>
#include <string>

/*

*/
class WinUsbDeviceManager
{
public:
    WinUsbDeviceManager();
    ~WinUsbDeviceManager();    
    static DWORD WINAPI staticRunEventLoop(void* Param);
    DWORD runEventLoop(void);
    void runEventLoopInThread();
protected:
    el::Logger* logger = el::Loggers::getLogger("WinUsbDeviceManager");
    std::unordered_map<TCHAR*, WinUsbDevice*> devicePathWinUsbDeviceMap;
    std::vector<TCHAR*> retrieveDevicePaths();
private:
};

