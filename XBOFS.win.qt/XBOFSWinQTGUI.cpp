#include "XBOFSWinQTGUI.h"
#include <vector>
#include <spdlog/sinks/null_sink.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include <qthread.h>
#include <qmessagebox.h>
#include <qevent.h>
#include <QtWidgets/QCheckBox>
#include <qdesktopservices.h>
#include <qstandardpaths.h>
#include <qdir.h>
#include <qfile.h>
#include <qsslsocket.h>
#include <fmt/core.h>
#include <shellapi.h>
#include <XBOFS.win/utils.h>
#include <XBOFS.win/WinUsbDeviceManager.h>

const auto installedMessage = QString::fromWCharArray(LR"""(
<span style="color:#2ECC40">Installed</span>
)""");

const auto vigEmBusNotInstalledMessage = QString::fromWCharArray(LR"""(
<span style="color:#ff0000">Not Installed!</span> Click <a href="https://github.com/ViGEm/ViGEmBus/releases/"><span style=" text-decoration: underline; color:#0000ff;">here</span></a> to visit the <span style=" font-size:8.25pt; font-weight:600;">VigEmBus</span> release page and download the latest installer
)""");

const auto xbofsWinDriverNotInstalledMessage = QString::fromWCharArray(LR"""(
<span style="color:#ff0000">Not Installed!</span> Click <a href="https://xbofs.win/zadig.html"><span style=" text-decoration: underline; color:#0000ff;">here</span></a> to open the <span style=" font-size:8.25pt; font-weight:600;">Driver Manager</span>
)""");

const auto currentVersionMessage = QString::fromWCharArray(LR"""(
<a href="https://github.com/OOPMan/XBOFS.win/releases/tag/%1"><span style=" text-decoration: underline; color:#0000ff;">%2</span></a>
)""");

const auto newVersionMessage = QString::fromWCharArray(LR"""(
<a href="https://github.com/OOPMan/XBOFS.win/releases/tag/%1"><span style=" text-decoration: underline; color:#FF4136;">%2</span></a> (A newer version is available! Click <a href="https://github.com/OOPMan/XBOFS.win/releases/tag/%3"><span style=" text-decoration: underline; color:#0000ff;">here</span></a> to visit the download page)
)""");

const auto prereleaseVersionMessage = QString::fromWCharArray(LR"""(
<a href="https://github.com/OOPMan/XBOFS.win/releases/tag/%1"><span style=" text-decoration: underline; color:#ff851b;">%2</span></a> (Warning: You are running a pre-release version of the software! Stability is not guaranteed!)
)""");

const auto versionCheckTLSErrorMessage = QString::fromWCharArray(LR"""(
<a href="https://github.com/OOPMan/XBOFS.win/releases/tag/%1"><span style=" text-decoration: underline; color:#ff851b;">%2</span></a> (Warning: Version check failed due to missing OpenSSL installation. Click <a href="http://slproweb.com/products/Win32OpenSSL.html"><span style=" text-decoration: underline; color:#0000ff;">here</span></a> to download OpenSSL installer)
)""");

void qtDesktopServicesOpenLink(const QString &link) 
{
    QDesktopServices::openUrl(link);
}

XBOFSWinQTGUI::XBOFSWinQTGUI(std::shared_ptr<spdlog::logger> logger, QWidget *parent)
: QMainWindow(parent), logger(logger)
{    
    // Settings
    settings = new QSettings(ORGANIZATION, APPLICATION, this);
    autostart = settings->value(SETTINGS_AUTOSTART, false).toBool();
    startMinimized = settings->value(SETTINGS_START_MINIMIZED, false).toBool();
    minimizeOnClose = settings->value(SETTINGS_MINIMIZE_ON_CLOSE, false).toBool();
    minimizeToTray = settings->value(SETTINGS_MINIMIZE_TO_TRAY, true).toBool();
    checkForUpdates = settings->value(SETTINGS_CHECK_FOR_UPDATES, true).toBool();
    // UI
    ui.setupUi(this);      
    ui.versionLabel->setText(currentVersionMessage.arg(VERSION, VERSION));
    ui.autostartCheckBox->setChecked(autostart);
    ui.startMinimizedCheckbox->setChecked(startMinimized);
    ui.minimizeOnCloseCheckBox->setChecked(minimizeOnClose);
    ui.minimizeToTrayCheckbox->setChecked(minimizeToTray);
    ui.updateCheckCheckbox->setChecked(checkForUpdates);
    connect(ui.actionDriver_Manager, &QAction::triggered, this, [&](bool checked) { handleDriverManagerLinkedClick(""); });
    connect(ui.actionExit, &QAction::triggered, this, &XBOFSWinQTGUI::handleSystemTrayMenuExit);
    connect(ui.autostartCheckBox, &QCheckBox::stateChanged, this, &XBOFSWinQTGUI::handleAutostartCheckboxStateChanged);
    connect(ui.startMinimizedCheckbox, &QCheckBox::stateChanged, this, &XBOFSWinQTGUI::handleStartMinimizedCheckboxStateChanged);
    connect(ui.minimizeOnCloseCheckBox, &QCheckBox::stateChanged, this, &XBOFSWinQTGUI::handleMinimizeOnCloseCheckboxStateChanged);
    connect(ui.minimizeToTrayCheckbox, &QCheckBox::stateChanged, this, &XBOFSWinQTGUI::handleMinimizeToTrayCheckboStateChanged);
    connect(ui.updateCheckCheckbox, &QCheckBox::stateChanged, this, &XBOFSWinQTGUI::handleUpdateCheckCheckboxStateChanged);
    connect(ui.versionLabel, &QLabel::linkActivated, &qtDesktopServicesOpenLink);
    connect(ui.homepageLabel, &QLabel::linkActivated, &qtDesktopServicesOpenLink);
    connect(ui.authorLabel, &QLabel::linkActivated, &qtDesktopServicesOpenLink);    
    connect(ui.specialThanksLabel, &QLabel::linkActivated, &qtDesktopServicesOpenLink);
    // Start WinUsbDeviceManager    
    winUsbDeviceManagerThread = new QThread();
    winUsbDeviceManager = new XBOFSWin::WinUsbDeviceManager(false, XBOFSWin::get_logger("WinUsbDeviceManager", logger->sinks()));
    connect(winUsbDeviceManagerThread, &QThread::finished, winUsbDeviceManager, &QObject::deleteLater);
    connect(winUsbDeviceManagerThread, &QThread::started, winUsbDeviceManager, &XBOFSWin::WinUsbDeviceManager::run);
    connect(winUsbDeviceManager, &XBOFSWin::WinUsbDeviceManager::winUsbDeviceManagerScanning, this, &XBOFSWinQTGUI::handleWinUsbDeviceManagerScanning);
    connect(winUsbDeviceManager, &XBOFSWin::WinUsbDeviceManager::winUsbDeviceAdded, this, &XBOFSWinQTGUI::handleWinUsbDeviceAdded);
    connect(winUsbDeviceManager, &XBOFSWin::WinUsbDeviceManager::winUsbDeviceRemoved, this, &XBOFSWinQTGUI::handleWinUsbDeviceRemoved);
    connect(this, &XBOFSWinQTGUI::startWinUsbDeviceThread, winUsbDeviceManager, &XBOFSWin::WinUsbDeviceManager::startWinUsbDeviceThread);
    connect(this, &XBOFSWinQTGUI::destroyed, this, &XBOFSWinQTGUI::handleTerminateWinUsbDeviceManager);
    winUsbDeviceManager->moveToThread(winUsbDeviceManagerThread);
    winUsbDeviceManagerThread->start();      
    // System tray icon
    if (QSystemTrayIcon::isSystemTrayAvailable()) {
        systemTrayIcon = new QSystemTrayIcon(windowIcon(), this);
        auto systemTrayIconMenu = new QMenu(this);
        auto restoreAction = systemTrayIconMenu->addAction("Restore");
        connect(restoreAction, &QAction::triggered, this, &XBOFSWinQTGUI::handleSystemTrayMenuRestore);
        auto exitAction = systemTrayIconMenu->addAction("Exit");
        connect(exitAction, &QAction::triggered, this, &XBOFSWinQTGUI::handleSystemTrayMenuExit);
        systemTrayIcon->setContextMenu(systemTrayIconMenu);        
        systemTrayIconEnabled = true;
    }
    // Check for VigEmBus driver
    if (XBOFSWin::vigEmBusAvailable()) ui.vigEmBusStatus->setText(installedMessage);
    else {        
        ui.vigEmBusStatus->setText(vigEmBusNotInstalledMessage);
        connect(ui.vigEmBusStatus, &QLabel::linkActivated, &qtDesktopServicesOpenLink);
    }
    // Check for XBOFS.win driver
    refreshXBOFSWinDriverStatus();
    // Update Check    
    if (checkForUpdates) {
        networkManager = new QNetworkAccessManager(this);
        connect(networkManager, &QNetworkAccessManager::finished, this, &XBOFSWinQTGUI::handleUpdateCheckResponse);
        networkManager->head(QNetworkRequest(QUrl("https://github.com/OOPMan/XBOFS.win/releases/latest")));
    }
    // Show or hide
    if (startMinimized) hide();
    else show();
}

void XBOFSWinQTGUI::handleDriverManagerLinkedClick(const QString& link)
{
    
    auto threadFinishedHandler = [&]() {
        driverManagerRunner->deleteLater();
        driverManagerThread->deleteLater();
        refreshXBOFSWinDriverStatus();

    };
    ui.xbofsWinDriverStatus->setText("<span style=\"color:#ff851b;\">Waiting for Driver Manager to exit...</span>");
    driverManagerThread = new QThread();
    driverManagerRunner = new DriverManagerRunner();
    connect(driverManagerThread, &QThread::started, driverManagerRunner, &DriverManagerRunner::run);
    connect(driverManagerThread, &QThread::finished, threadFinishedHandler);
    driverManagerRunner->moveToThread(driverManagerThread);
    driverManagerThread->start();
}

void XBOFSWinQTGUI::refreshXBOFSWinDriverStatus()
{
    auto status = XBOFSWin::XBOFSWinDeviceInstalled();
    ui.xbofsWinDriverStatus->setText(
        XBOFSWin::XBOFSWinDeviceInstalled() ? installedMessage : xbofsWinDriverNotInstalledMessage
    );
    if (!status) connect(ui.xbofsWinDriverStatus, &QLabel::linkActivated, this, &XBOFSWinQTGUI::handleDriverManagerLinkedClick, Qt::SingleShotConnection);
}

std::optional<std::pair<int, std::vector<std::tuple<std::wstring, WinUsbDeviceTabWidget*>>::iterator>> XBOFSWinQTGUI::getIteratorForDevicePath(const std::wstring &devicePath) {
    auto iterator = tabs.begin();
    int index;
    for (index = 1; iterator != tabs.end(); index++) {
        auto currentDevicePath = std::get<0>(*iterator);
        if (currentDevicePath == devicePath) break;
        ++iterator;
    }
    if (iterator == tabs.end()) return std::nullopt;
    return std::optional<std::pair<int, std::vector<std::tuple<std::wstring, WinUsbDeviceTabWidget*>>::iterator>>{std::make_pair(index, iterator)};
}

void XBOFSWinQTGUI::handleWinUsbDeviceAdded(const std::wstring &devicePath, const XBOFSWin::WinUsbDevice *winUsbDevice) {        
    // Update UI    
    auto devicePathQString = QString::fromStdWString(devicePath);
    auto tabWidget = new WinUsbDeviceTabWidget(ui.tabWidget, devicePathQString, winUsbDevice, logger);
    auto tabIndex = ui.tabWidget->addTab(tabWidget, QString());    
    ui.tabWidget->setTabText(tabIndex, QString::fromStdWString(fmt::format(L"Stick {}", tabIndex)));
    tabs.push_back(std::make_tuple(devicePath, tabWidget));
    emit startWinUsbDeviceThread(devicePath);
}

void XBOFSWinQTGUI::handleWinUsbDeviceRemoved(const std::wstring &devicePath) {    
    auto optionalIterator = getIteratorForDevicePath(devicePath);
    if (!optionalIterator) return;
    auto tuple = *optionalIterator;
    auto index = tuple.first;
    auto iterator = tuple.second;
    auto tabWidget = std::get<1>(*iterator);
    tabs.erase(iterator);
    ui.tabWidget->removeTab(index);
    delete tabWidget;
    for (auto idx = 1; idx < ui.tabWidget->count(); idx++) {
        ui.tabWidget->setTabText(idx, QString::fromStdWString(fmt::format(L"Stick {}", idx)));
    }
}

void XBOFSWinQTGUI::handleWinUsbDeviceManagerScanning() {
    ui.xbofsWinDeviceManagerStatus->setText(QString::fromWCharArray(LR"""(<span style="color:#2ECC40">Scanning for supported controllers...</span>)"""));
}

void XBOFSWinQTGUI::handleTerminateWinUsbDeviceManager() {    
    logger->info("Requesting interruption of thread handling WinUsbDeviceManager");
    winUsbDeviceManagerThread->requestInterruption();
    logger->info("Signalling thread handling WinUsbDeviceManager to quit");
    winUsbDeviceManagerThread->quit();
    logger->info("Waiting for thread hanlding WinUsbDeviceManager to quit");
    winUsbDeviceManagerThread->wait();
    delete winUsbDeviceManagerThread;
    logger->flush();
}

void XBOFSWinQTGUI::handleSystemTrayMenuRestore(const bool &checked) {
    setWindowFlags(previousFlags);
    showNormal();
}


void XBOFSWinQTGUI::handleSystemTrayMenuExit(const bool &checked) {                
    systemTrayIconEnabled = false;              
    QApplication::quit();
}

void XBOFSWinQTGUI::closeEvent(QCloseEvent *event) {
    if (systemTrayIconEnabled && minimizeOnClose) {        
        hide();
        event->ignore();
    }
    else handleSystemTrayMenuExit(true);
}

void XBOFSWinQTGUI::hideEvent(QHideEvent *event) {    
    if (systemTrayIconEnabled && minimizeToTray) {
        systemTrayIcon->show();
        previousFlags = windowFlags();
        setWindowFlags(Qt::ToolTip);
    }
}

void XBOFSWinQTGUI::showEvent(QShowEvent *event) {
    if (systemTrayIconEnabled) {
        systemTrayIcon->hide();        
    }
}

void XBOFSWinQTGUI::handleAutostartCheckboxStateChanged(const quint16 state) {
    autostart = state == Qt::Checked;
    settings->setValue(SETTINGS_AUTOSTART, autostart);    
    auto applicationFilePath = QApplication::applicationFilePath();
    auto applicationsLocation = QStandardPaths::writableLocation(QStandardPaths::ApplicationsLocation);
    auto linkPath = applicationsLocation + QDir::separator() + "Startup" + QDir::separator() + "XBOFS.win.qt5.lnk";
    if (autostart) QFile::link(applicationFilePath, linkPath);
    else QFile::remove(linkPath);
}

void XBOFSWinQTGUI::handleStartMinimizedCheckboxStateChanged(const quint16 state) {
    startMinimized = state == Qt::Checked;
    settings->setValue(SETTINGS_START_MINIMIZED, startMinimized);
}

void XBOFSWinQTGUI::handleMinimizeOnCloseCheckboxStateChanged(const quint16 state) {
    minimizeOnClose = state == Qt::Checked;
    settings->setValue(SETTINGS_MINIMIZE_ON_CLOSE, minimizeOnClose);
}

void XBOFSWinQTGUI::handleMinimizeToTrayCheckboStateChanged(const quint16 state) {
    minimizeToTray = state == Qt::Checked;
    settings->setValue(SETTINGS_MINIMIZE_TO_TRAY, minimizeToTray);
}

void XBOFSWinQTGUI::handleUpdateCheckCheckboxStateChanged(const quint16 state) {
    checkForUpdates = state == Qt::Checked;
    settings->setValue(SETTINGS_CHECK_FOR_UPDATES, checkForUpdates);
}

void XBOFSWinQTGUI::handleUpdateCheckResponse(QNetworkReply *response) {
    response->deleteLater();        
    auto errorCode = response->error();
    if (errorCode == QNetworkReply::UnknownNetworkError && response->errorString().contains("TLS")) 
        ui.versionLabel->setText(versionCheckTLSErrorMessage.arg(VERSION, VERSION));    
    if (errorCode != QNetworkReply::NoError) return;
    auto location = response->header(QNetworkRequest::LocationHeader).toString();
    auto versionTag = location.split('/').back();
    if (VERSION < versionTag) ui.versionLabel->setText(newVersionMessage.arg(VERSION, VERSION, versionTag));
    else if (VERSION > versionTag) ui.versionLabel->setText(prereleaseVersionMessage.arg(VERSION, VERSION));
}

void DriverManagerRunner::run() {
    auto directory = QApplication::applicationDirPath().toStdWString();
    SHELLEXECUTEINFO shellExecInfo = { 0 };
    shellExecInfo.cbSize = sizeof(shellExecInfo);
    shellExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
    shellExecInfo.hwnd = 0;
    shellExecInfo.lpVerb = L"runas";
    shellExecInfo.lpFile = L"drivermanager.exe";
    shellExecInfo.lpDirectory = directory.c_str();
    shellExecInfo.lpParameters = L"";
    shellExecInfo.nShow = SW_SHOW;
    shellExecInfo.hInstApp = 0;
    if (ShellExecuteEx(&shellExecInfo))
    {
        WaitForSingleObject(shellExecInfo.hProcess, INFINITE);
        CloseHandle(shellExecInfo.hProcess);
    }
    QThread::currentThread()->quit();
}