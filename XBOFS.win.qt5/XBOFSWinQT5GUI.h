#pragma once

#include <spdlog/spdlog.h>
#include <XBOFS.win/WinUsbDeviceManager.h>
#include <XBOFS.win/WinUsbDevice.h>

#include <QtWidgets/QMainWindow>
#include "ui_XBOFSWinQT5GUI.h"
#include "ui_WinUsbDeviceWidget.h"

namespace std {
    template<> struct hash<QString> {
        std::size_t operator()(const QString& s) const {
            return qHash(s);
        }
    };
}

class XBOFSWinQT5GUI : public QMainWindow
{
    Q_OBJECT

public:
    XBOFSWinQT5GUI(QWidget *parent = Q_NULLPTR);

public slots:
    void winUsbDeviceAdded(const QString &devicePath, const XBOFSWin::WinUsbDevice *winUsbDevice);
    void winUsbDeviceRemoved(const QString &devicePath, const XBOFSWin::WinUsbDevice *winUsbDevice);
    void winUsbDeviceManagerScanning();
    void terminateWinUsbDeviceManager();

protected:
    Ui::XBOFSWinQT5GUIClass ui;        
    std::shared_ptr<spdlog::logger> logger;
    QThread *winUsbDeviceManagerThread;
    XBOFSWin::WinUsbDeviceManager *winUsbDeviceManager;

    std::unordered_map<QString, std::tuple<int, QWidget*, Ui::WinUsbDeviceWidget*>> devicePathTabMap;
};
