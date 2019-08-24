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

private:
    Ui::XBOFSWinQT5GUIClass ui;
    XBOFSWin::WinUsbDeviceManager *winUsbDeviceManager;
    std::shared_ptr<spdlog::logger> logger;
};
