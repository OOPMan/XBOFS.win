#pragma once
#include <XBOFS.win/pch.h>
#include <XBOFS.win/WinUsbDevice.h>
#include <cfgmgr32.h>
#include <qobject.h>
#include <qthread.h>

/*

*/
namespace XBOFSWin {

    class WinUsbDeviceManager : public QObject
    {
        Q_OBJECT
    public:        
        WinUsbDeviceManager(std::shared_ptr<spdlog::logger> logger, QObject* parent=nullptr);
        ~WinUsbDeviceManager() {};

    public slots:
        void run();
        void startWinUsbDeviceThread(const std::wstring& devicePath);

    signals:
        void winUsbDeviceAdded(const std::wstring &devicePath, const XBOFSWin::WinUsbDevice *winUsbDevice);
        void winUsbDeviceRemoved(const std::wstring &devicePath);
        void winUsbDeviceManagerScanning();
        void winUsbDeviceManagerSleeping();
        void winUsbDeviceManagerTerminating();

    protected:
        const std::shared_ptr<spdlog::logger> logger;
        std::unordered_map<std::wstring, std::pair<QThread*, WinUsbDevice*>> devicePathWinUsbDeviceMap;
        std::set<std::wstring> previousDevicePaths;

        std::set<std::wstring> retrieveDevicePaths();              
    };
}

