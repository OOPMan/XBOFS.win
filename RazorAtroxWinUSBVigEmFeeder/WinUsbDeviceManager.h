#pragma once
#include "pch.h"
/*

*/
class WinUsbDeviceManager
{
public:
    WinUsbDeviceManager();
    ~WinUsbDeviceManager();
    // TODO: Rename these later
    static DWORD WINAPI StaticThreadStart(void* Param);
    DWORD ThreadStart(void);
    void startMyThread();
protected:
private:
};

