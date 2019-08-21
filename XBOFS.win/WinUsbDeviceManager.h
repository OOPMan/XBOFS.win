#pragma once
#include "pch.h"
#include "Thread.h"
#include "WinUsbDevice.h"

#include <cfgmgr32.h>

/*

*/
namespace XBOFSWin {

    class WinUsbDeviceManager : public Thread
    {
    public:
        WinUsbDeviceManager(std::shared_ptr<spdlog::logger> logger, DWORD parentThreadId, DWORD uiManagerThreadId);
        ~WinUsbDeviceManager() {};

        DWORD run();

    protected:
        std::set<tstring> retrieveDevicePaths();

    };
}

