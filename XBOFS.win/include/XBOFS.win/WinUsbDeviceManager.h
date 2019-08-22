#pragma once
#include <XBOFS.win/pch.h>
#include <XBOFS.win/Thread.h>
#include <XBOFS.win/WinUsbDevice.h>
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

