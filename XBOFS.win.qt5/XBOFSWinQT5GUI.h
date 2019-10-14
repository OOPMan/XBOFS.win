#pragma once

#include <spdlog/spdlog.h>
#include <XBOFS.win/WinUsbDeviceManager.h>
#include <XBOFS.win/WinUsbDevice.h>

#include <QtWidgets/QMainWindow>
#include "ui_XBOFSWinQT5GUI.h"


class XBOFSWinQT5GUI : public QMainWindow
{
    Q_OBJECT

public:
    XBOFSWinQT5GUI(QWidget *parent = Q_NULLPTR);

public slots:
    void winUsbDeviceAdded(const QString &identifier, const XBOFSWin::WinUsbDevice &winUsbDevice);
    void winUsbDeviceRemoved(const QString &identifier, const XBOFSWin::WinUsbDevice &winUsbDevice);
    void winUsbDeviceManagerScanning();
    void terminateWinUsbDeviceManager();

protected:
    Ui::XBOFSWinQT5GUIClass ui;        
    std::shared_ptr<spdlog::logger> logger;
    QThread *winUsbDeviceManagerThread;
    XBOFSWin::WinUsbDeviceManager *winUsbDeviceManager;
};
