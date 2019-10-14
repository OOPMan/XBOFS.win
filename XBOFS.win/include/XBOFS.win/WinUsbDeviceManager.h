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
        WinUsbDeviceManager(std::string identifier, std::shared_ptr<spdlog::logger> logger, QObject* parent=nullptr);
        ~WinUsbDeviceManager() {};

    public slots:
        void run();

    signals:
        void winUsbDeviceAdded(const QString &identifier, const XBOFSWin::WinUsbDevice &winUsbDevice);        
        void winUsbDeviceRemoved(const QString &identifier, const XBOFSWin::WinUsbDevice &winUsbDevice);
        void winUsbDeviceManagerScanning();
        void winUsbDeviceManagerSleeping();
        void winUsbDeviceManagerTerminating();

    protected:
        const std::string identifier;
        const std::shared_ptr<spdlog::logger> logger;

        std::set<tstring> retrieveDevicePaths();        
    };
}

