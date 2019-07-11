#pragma once
#include "pch.h"
#include "WinUsbDevice.h"
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
    // TODO: Rename these later
    static DWORD WINAPI staticRunEventLoop(void* Param);
    DWORD runEventLoop(void);
    void runEventLoopInThread();
protected:
    std::unordered_map<TCHAR*, WinUsbDevice*> devicePathWinUsbDeviceMap;
    std::vector<TCHAR*> retrieveDevicePaths();
private:
};

