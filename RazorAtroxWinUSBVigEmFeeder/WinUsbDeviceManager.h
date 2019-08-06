#pragma once
#include "pch.h"
#include "Thread.h"
#include "WinUsbDevice.h"

#include <cfgmgr32.h>

/*

*/
class WinUsbDeviceManager : public Thread
{
public:    
    WinUsbDeviceManager(DWORD parentThreadId, DWORD uiManagerThreadId);
    ~WinUsbDeviceManager() {};

    DWORD run();
    
protected:
    std::set<tstring> retrieveDevicePaths();

};

