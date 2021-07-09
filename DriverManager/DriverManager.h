#pragma once
#include <Windows.h>
#include <tchar.h>
#include <strsafe.h>
#include <winusb.h>
#include <usb.h>
#include <cfgmgr32.h>
#include <set>
#include <libwdi/libwdi.h>
#include <XBOFS.win/device.h>
#include <QtWidgets/QMainWindow>
#include "ui_DriverManager.h"

class DriverManager : public QMainWindow
{
    Q_OBJECT

public:
    DriverManager(QWidget *parent = Q_NULLPTR);

public slots:
    void handleRazerAtroxXBODriverPushButtonClicked(bool checked = false);
    void handleMadcatzTE2XBODriverPushButtonClicked(bool checked = false);

protected:
    Ui::DriverManagerClass ui;
    std::unordered_map<std::wstring, QPushButton*> deviceButtonMap;

    int installDriver(QString driverName, unsigned short vendorId, unsigned short productId);
};
