#pragma once

#include <optional>
#include <spdlog/spdlog.h>
#include <XBOFS.win/WinUsbDeviceManager.h>
#include <XBOFS.win/WinUsbDevice.h>

#include <QtWidgets/QMainWindow>
#include <qnetworkaccessmanager.h>
#include <qnetworkreply.h>
#include <qsystemtrayicon.h>
#include <qsettings.h>
#include <qstring.h>
#include "ui_XBOFSWinQT5GUI.h"
#include "ui_WinUsbDeviceWidget.h"

const QString VERSION("v0.5.0");
const QString SETTINGS_AUTOSTART("autostart");
const QString SETTINGS_START_MINIMIZED("startMinimized");
const QString SETTINGS_MINIMIZE_TO_TRAY("minimizeToTray");
const QString SETTINGS_MINIMIZE_ON_CLOSE("minimizeOnClose");
const QString SETTINGS_CHECK_FOR_UPDATES("checkForUpdates");

class XBOFSWinQT5GUI : public QMainWindow
{
    Q_OBJECT

public:
    XBOFSWinQT5GUI(std::shared_ptr<spdlog::logger> logger, QWidget *parent = Q_NULLPTR);

public slots:
    void handleWinUsbDeviceAdded(const std::wstring &devicePath, const XBOFSWin::WinUsbDevice *winUsbDevice);
    void handleWinUsbDeviceRemoved(const std::wstring &devicePath);
    void handleWinUsbDeviceManagerScanning();
    void handleTerminateWinUsbDeviceManager();
    void handleVigEmConnect(const std::wstring &devicePath);
    void handleVigEmConnected(const std::wstring &devicePath);
    void handleVigEmTargetAdd(const std::wstring &devicePath);
    void handleVigEmTargetAdded(const std::wstring &devicePath);
    void handleVigEmTargetInfo(const std::wstring &devicePath, quint16 vendorId, quint16 productId, const ulong index);
    void handleVigEmError(const std::wstring &devicePath);
    void handleWinUsbDeviceOpen(const std::wstring &devicePath);
    void handleWinUsbDeviceInfo(const std::wstring &devicePath, quint16 vendorId, quint16 productId,
                                const std::wstring &manufacturer, const std::wstring &product, const std::wstring &serialNumber);
    void handleWinUsbDeviceOpened(const std::wstring &devicePath);
    void handleWinUsbDeviceInit(const std::wstring &devicePath);
    void handleWinUsbDeviceInitComplete(const std::wstring &devicePath);
    void handleWinUsbDeviceReadingInput(const std::wstring &devicePath);
    void handleWinUsbDeviceTerminating(const std::wstring &devicePath);
    void handleWinUsbDeviceError(const std::wstring &devicePath);

    void handleSystemTrayMenuRestore(const bool &checked);
    void handleSystemTrayMenuExit(const bool &checked);

    void handleAutostartCheckboxStateChanged(const quint16 state);
    void handleStartMinimizedCheckboxStateChanged(const quint16 state);
    void handleMinimizeToTrayCheckboStateChanged(const quint16 state);
    void handleMinimizeOnCloseCheckboxStateChanged(const quint16 state);
    void handleUpdateCheckCheckboxStateChanged(const quint16 state);
    
    void handleUpdateCheckResponse(QNetworkReply *response);

protected:        
    Ui::XBOFSWinQT5GUIClass ui;     
    QSettings *settings; 
    QNetworkAccessManager *networkManager;
    bool autostart = false;
    bool startMinimized = false;    
    bool minimizeToTray = false;
    bool minimizeOnClose = false;
    bool checkForUpdates = false;

    QSystemTrayIcon *systemTrayIcon;
    bool systemTrayIconEnabled = false;
    Qt::WindowFlags previousFlags;

    const std::shared_ptr<spdlog::logger> logger;
    QThread *winUsbDeviceManagerThread;
    XBOFSWin::WinUsbDeviceManager *winUsbDeviceManager;

    std::vector<std::tuple<std::wstring, QWidget*, Ui::WinUsbDeviceWidget*>> tabs;    

    std::optional<std::pair<int, std::vector<std::tuple<std::wstring, QWidget*, Ui::WinUsbDeviceWidget*>>::iterator>> getIteratorForDevicePath(const std::wstring &devicePath);    

    void closeEvent(QCloseEvent *event);
    void hideEvent(QHideEvent *event);
    void showEvent(QShowEvent *event);
};
