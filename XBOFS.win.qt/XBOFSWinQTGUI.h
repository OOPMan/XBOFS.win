#pragma once

#include <optional>
#include <spdlog/spdlog.h>
#include <XBOFS.win/WinUsbDeviceManager.h>
#include <XBOFS.win/WinUsbDevice.h>

#include <qmainwindow.h>
#include <qnetworkaccessmanager.h>
#include <qnetworkreply.h>
#include <qsystemtrayicon.h>
#include <qsettings.h>
#include <qstring.h>
#include <XBOFS.win/constants.h>
#include "WinUsbDeviceTabWidget.h"
#include "ui_XBOFSWinQTGUI.h"
#include "ui_WinUsbDeviceWidget.h"

const QString VERSION("v1.0.0");

using namespace XBOFSWin::settings;

const QString SETTINGS_AUTOSTART("autostart");
const QString SETTINGS_START_MINIMIZED("startMinimized");
const QString SETTINGS_MINIMIZE_TO_TRAY("minimizeToTray");
const QString SETTINGS_MINIMIZE_ON_CLOSE("minimizeOnClose");
const QString SETTINGS_CHECK_FOR_UPDATES("checkForUpdates");

class DriverManagerRunner : public QObject
{
    Q_OBJECT

public:
    DriverManagerRunner(QObject* parent = Q_NULLPTR) : QObject(parent) {};

public slots:
    void run();
};

class XBOFSWinQTGUI : public QMainWindow
{
    Q_OBJECT

public:
    XBOFSWinQTGUI(std::shared_ptr<spdlog::logger> logger, QWidget *parent = Q_NULLPTR);

public slots:
    void handleDriverManagerLinkedClick(const QString& link);

    void handleWinUsbDeviceAdded(const std::wstring &devicePath, const XBOFSWin::WinUsbDevice *winUsbDevice);
    void handleWinUsbDeviceRemoved(const std::wstring &devicePath);
    void handleWinUsbDeviceManagerScanning();
    void handleTerminateWinUsbDeviceManager();

    void handleSystemTrayMenuRestore(const bool &checked);
    void handleSystemTrayMenuExit(const bool &checked);

    void handleAutostartCheckboxStateChanged(const quint16 state);
    void handleStartMinimizedCheckboxStateChanged(const quint16 state);
    void handleMinimizeToTrayCheckboStateChanged(const quint16 state);
    void handleMinimizeOnCloseCheckboxStateChanged(const quint16 state);
    void handleUpdateCheckCheckboxStateChanged(const quint16 state);
    
    void handleUpdateCheckResponse(QNetworkReply *response);

signals:
    void startWinUsbDeviceThread(const std::wstring devicePath);

protected:        
    Ui::XBOFSWinQT5GUIClass ui;     
    QSettings *settings; 
    QNetworkAccessManager *networkManager;
    bool autostart = false;
    bool startMinimized = false;    
    bool minimizeToTray = false;
    bool minimizeOnClose = false;
    bool checkForUpdates = false;

    QThread* driverManagerThread;
    DriverManagerRunner *driverManagerRunner;

    QSystemTrayIcon *systemTrayIcon;
    bool systemTrayIconEnabled = false;
    Qt::WindowFlags previousFlags;

    const std::shared_ptr<spdlog::logger> logger;
    QThread *winUsbDeviceManagerThread;
    XBOFSWin::WinUsbDeviceManager *winUsbDeviceManager;

    std::vector<std::tuple<std::wstring, WinUsbDeviceTabWidget*>> tabs;    

    std::optional<std::pair<int, std::vector<std::tuple<std::wstring, WinUsbDeviceTabWidget*>>::iterator>> getIteratorForDevicePath(const std::wstring &devicePath);    

    void refreshXBOFSWinDriverStatus();
    void closeEvent(QCloseEvent *event);
    void hideEvent(QHideEvent *event);
    void showEvent(QShowEvent *event);
};
