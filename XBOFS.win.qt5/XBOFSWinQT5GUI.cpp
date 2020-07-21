#include "XBOFSWinQT5GUI.h"
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
#include <qnetworkconfiguration.h>
#include <qsslsocket.h>
#include <fmt/core.h>
#include <XBOFS.win/utils.h>
#include <XBOFS.win/WinUsbDeviceManager.h>

const auto installedMessage = QString::fromWCharArray(LR"""(
<span style="color:#2ECC40">Installed</span>
)""");

const auto vigEmBusNotInstalledMessage = QString::fromWCharArray(LR"""(
<span style="color:#ff0000">Not Installed!</span> Click <a href="https://github.com/ViGEm/ViGEmBus/releases/"><span style=" text-decoration: underline; color:#0000ff;">here</span></a> to visit the <span style=" font-size:8.25pt; font-weight:600;">VigEmBus</span> release page and download the latest installer
)""");

const auto xbofsWinDriverNotInstalledMessage = QString::fromWCharArray(LR"""(
<span style="color:#ff0000">Not Installed!</span> Click <a href="https://xbofs.win/zadig.html"><span style=" text-decoration: underline; color:#0000ff;">here</span></a> to visit the <span style=" font-size:8.25pt; font-weight:600;">XBOFS.win</span> ZaDig WinUSB driver installation guide
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

void qtDesktopServicesOpenLink(const QString & link) {
    QDesktopServices::openUrl(link);
}

XBOFSWinQT5GUI::XBOFSWinQT5GUI(std::shared_ptr<spdlog::logger> logger, QWidget *parent)
: QMainWindow(parent), logger(logger)
{    
    // Settings
    settings = new QSettings("OOPMan", "XBOFS.win", this);
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
    connect(ui.actionExit, &QAction::triggered, this, &XBOFSWinQT5GUI::handleSystemTrayMenuExit);
    connect(ui.autostartCheckBox, &QCheckBox::stateChanged, this, &XBOFSWinQT5GUI::handleAutostartCheckboxStateChanged);
    connect(ui.startMinimizedCheckbox, &QCheckBox::stateChanged, this, &XBOFSWinQT5GUI::handleStartMinimizedCheckboxStateChanged);
    connect(ui.minimizeOnCloseCheckBox, &QCheckBox::stateChanged, this, &XBOFSWinQT5GUI::handleMinimizeOnCloseCheckboxStateChanged);
    connect(ui.minimizeToTrayCheckbox, &QCheckBox::stateChanged, this, &XBOFSWinQT5GUI::handleMinimizeToTrayCheckboStateChanged);
    connect(ui.updateCheckCheckbox, &QCheckBox::stateChanged, this, &XBOFSWinQT5GUI::handleUpdateCheckCheckboxStateChanged);
    connect(ui.versionLabel, &QLabel::linkActivated, &qtDesktopServicesOpenLink);
    connect(ui.homepageLabel, &QLabel::linkActivated, &qtDesktopServicesOpenLink);
    connect(ui.authorLabel, &QLabel::linkActivated, &qtDesktopServicesOpenLink);    
    connect(ui.specialThanksLabel, &QLabel::linkActivated, &qtDesktopServicesOpenLink);
    // Start WinUsbDeviceManager    
    winUsbDeviceManagerThread = new QThread();
    winUsbDeviceManager = new XBOFSWin::WinUsbDeviceManager(XBOFSWin::get_logger("WinUsbDeviceManager", logger->sinks()));
    connect(winUsbDeviceManagerThread, &QThread::finished, winUsbDeviceManager, &QObject::deleteLater);
    connect(winUsbDeviceManagerThread, &QThread::started, winUsbDeviceManager, &XBOFSWin::WinUsbDeviceManager::run);
    connect(winUsbDeviceManager, &XBOFSWin::WinUsbDeviceManager::winUsbDeviceManagerScanning, this, &XBOFSWinQT5GUI::handleWinUsbDeviceManagerScanning);
    connect(winUsbDeviceManager, &XBOFSWin::WinUsbDeviceManager::winUsbDeviceAdded, this, &XBOFSWinQT5GUI::handleWinUsbDeviceAdded);
    connect(winUsbDeviceManager, &XBOFSWin::WinUsbDeviceManager::winUsbDeviceRemoved, this, &XBOFSWinQT5GUI::handleWinUsbDeviceRemoved);
    connect(this, &XBOFSWinQT5GUI::destroyed, this, &XBOFSWinQT5GUI::handleTerminateWinUsbDeviceManager);
    winUsbDeviceManager->moveToThread(winUsbDeviceManagerThread);
    winUsbDeviceManagerThread->start();      
    // System tray icon
    if (QSystemTrayIcon::isSystemTrayAvailable()) {
        systemTrayIcon = new QSystemTrayIcon(windowIcon(), this);
        auto systemTrayIconMenu = new QMenu(this);
        auto restoreAction = systemTrayIconMenu->addAction("Restore");
        connect(restoreAction, &QAction::triggered, this, &XBOFSWinQT5GUI::handleSystemTrayMenuRestore);
        auto exitAction = systemTrayIconMenu->addAction("Exit");
        connect(exitAction, &QAction::triggered, this, &XBOFSWinQT5GUI::handleSystemTrayMenuExit);
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
    if (XBOFSWin::XBOFSWinDeviceInstalled()) ui.xbofsWinDriverStatus->setText(installedMessage);
    else {        
        ui.xbofsWinDriverStatus->setText(xbofsWinDriverNotInstalledMessage);
        connect(ui.xbofsWinDriverStatus, &QLabel::linkActivated, &qtDesktopServicesOpenLink);
    }
    // Update Check    
    if (checkForUpdates) {
        networkManager = new QNetworkAccessManager(this);
        connect(networkManager, &QNetworkAccessManager::finished, this, &XBOFSWinQT5GUI::handleUpdateCheckResponse);
        networkManager->head(QNetworkRequest(QUrl("https://github.com/OOPMan/XBOFS.win/releases/latest")));
    }
    // Show or hide
    show();
    if (startMinimized) hide();    
}

std::optional<std::pair<int, std::vector<std::tuple<std::wstring, QWidget*, Ui::WinUsbDeviceWidget*>>::iterator>> XBOFSWinQT5GUI::getIteratorForDevicePath(const std::wstring &devicePath) {
    auto iterator = tabs.begin();
    int index;
    for (index = 1; iterator != tabs.end(); index++) {
        auto currentDevicePath = std::get<0>(*iterator);
        if (currentDevicePath == devicePath) break;
        ++iterator;
    }
    if (iterator == tabs.end()) return std::nullopt;
    return std::optional<std::pair<int, std::vector<std::tuple<std::wstring, QWidget*, Ui::WinUsbDeviceWidget*>>::iterator>>{std::make_pair(index, iterator)};
}

void XBOFSWinQT5GUI::handleWinUsbDeviceAdded(const std::wstring &devicePath, const XBOFSWin::WinUsbDevice *winUsbDevice) {        
    // Connect signals    
    connect(winUsbDevice, &XBOFSWin::WinUsbDevice::vigEmConnect, this, &XBOFSWinQT5GUI::handleVigEmConnect);
    connect(winUsbDevice, &XBOFSWin::WinUsbDevice::vigEmConnected, this, &XBOFSWinQT5GUI::handleVigEmConnected);
    connect(winUsbDevice, &XBOFSWin::WinUsbDevice::vigEmTargetAdd, this, &XBOFSWinQT5GUI::handleVigEmTargetAdd);
    connect(winUsbDevice, &XBOFSWin::WinUsbDevice::vigEmTargetAdded, this, &XBOFSWinQT5GUI::handleVigEmTargetAdded);
    connect(winUsbDevice, &XBOFSWin::WinUsbDevice::vigEmTargetInfo, this, &XBOFSWinQT5GUI::handleVigEmTargetInfo);
    connect(winUsbDevice, &XBOFSWin::WinUsbDevice::vigEmError, this, &XBOFSWinQT5GUI::handleVigEmError);
    connect(winUsbDevice, &XBOFSWin::WinUsbDevice::winUsbDeviceOpen, this, &XBOFSWinQT5GUI::handleWinUsbDeviceOpen);
    connect(winUsbDevice, &XBOFSWin::WinUsbDevice::winUsbDeviceOpened, this, &XBOFSWinQT5GUI::handleWinUsbDeviceOpened);
    connect(winUsbDevice, &XBOFSWin::WinUsbDevice::winUsbDeviceInfo, this, &XBOFSWinQT5GUI::handleWinUsbDeviceInfo);
    connect(winUsbDevice, &XBOFSWin::WinUsbDevice::winUsbDeviceInit, this, &XBOFSWinQT5GUI::handleWinUsbDeviceInit);
    connect(winUsbDevice, &XBOFSWin::WinUsbDevice::winUsbDeviceInitComplete, this, &XBOFSWinQT5GUI::handleWinUsbDeviceInitComplete);
    connect(winUsbDevice, &XBOFSWin::WinUsbDevice::winUsbDeviceReadingInput, this, &XBOFSWinQT5GUI::handleWinUsbDeviceReadingInput);
    connect(winUsbDevice, &XBOFSWin::WinUsbDevice::winUsbDeviceTerminating, this, &XBOFSWinQT5GUI::handleWinUsbDeviceTerminating);
    connect(winUsbDevice, &XBOFSWin::WinUsbDevice::winUsbDeviceError, this, &XBOFSWinQT5GUI::handleWinUsbDeviceError);
    // Update UI    
    auto devicePathQString = QString::fromStdWString(devicePath);
    auto tabWidget = new QWidget();
    auto tabWidgetUi = new Ui::WinUsbDeviceWidget();
    tabWidget->setObjectName(devicePathQString);
    tabWidgetUi->setupUi(tabWidget);    
    auto tabIndex = ui.tabWidget->addTab(tabWidget, QString());    
    ui.tabWidget->setTabText(tabIndex, QString::fromStdWString(fmt::format(L"Stick {}", tabIndex)));
    tabs.push_back(std::make_tuple(devicePath, tabWidget, tabWidgetUi));
}

void XBOFSWinQT5GUI::handleWinUsbDeviceRemoved(const std::wstring &devicePath) {    
    auto optionalIterator = getIteratorForDevicePath(devicePath);
    if (!optionalIterator) return;
    auto tuple = *optionalIterator;
    auto index = tuple.first;
    auto iterator = tuple.second;
    auto tabWidget = std::get<1>(*iterator);
    auto tabWidgetUi = std::get<2>(*iterator);
    tabs.erase(iterator);
    ui.tabWidget->removeTab(index);
    delete tabWidget;
    delete tabWidgetUi;
    for (auto idx = 1; idx < ui.tabWidget->count(); idx++) {
        ui.tabWidget->setTabText(idx, QString::fromStdWString(fmt::format(L"Stick {}", idx)));
    }
}

void XBOFSWinQT5GUI::handleVigEmConnect(const std::wstring &devicePath) {
    auto optionalIterator = getIteratorForDevicePath(devicePath);
    if (!optionalIterator) return;
    auto iterator = (*optionalIterator).second;
    auto tabWidgetUi = std::get<2>(*iterator);
    tabWidgetUi->vigEmClientStatus->setText(QString::fromUtf8("Connecting..."));
}

void XBOFSWinQT5GUI::handleVigEmConnected(const std::wstring &devicePath) {
    auto optionalIterator = getIteratorForDevicePath(devicePath);
    if (!optionalIterator) return;
    auto iterator = (*optionalIterator).second;
    auto tabWidgetUi = std::get<2>(*iterator);
    tabWidgetUi->vigEmClientStatus->setText(QString::fromUtf8("Connected"));
}

void XBOFSWinQT5GUI::handleVigEmTargetAdd(const std::wstring &devicePath) {    
    auto optionalIterator = getIteratorForDevicePath(devicePath);
    if (!optionalIterator) return;
    auto iterator = (*optionalIterator).second;
    auto tabWidgetUi = std::get<2>(*iterator);
    tabWidgetUi->vigEmTargetStatus->setText(QString::fromUtf8("Adding..."));
}

void XBOFSWinQT5GUI::handleVigEmTargetAdded(const std::wstring &devicePath) {
    auto optionalIterator = getIteratorForDevicePath(devicePath);
    if (!optionalIterator) return;
    auto iterator = (*optionalIterator).second;
    auto tabWidgetUi = std::get<2>(*iterator);
    tabWidgetUi->vigEmTargetStatus->setText(QString::fromUtf8("Added")); // TODO: Display more details on target
}

void XBOFSWinQT5GUI::handleVigEmTargetInfo(const std::wstring &devicePath, quint16 vendorId, quint16 productId, const ulong index) {
    auto optionalIterator = getIteratorForDevicePath(devicePath);
    if (!optionalIterator) return;
    auto iterator = (*optionalIterator).second;
    auto tabWidgetUi = std::get<2>(*iterator);
    tabWidgetUi->virtualDeviceVendorID->setText(QString::fromStdString(fmt::format("0x{:04X}", vendorId)));
    tabWidgetUi->virtualDeviceProductID->setText(QString::fromStdString(fmt::format("0x{:04X}", productId)));
    tabWidgetUi->virtualDeviceUserIndex->setText(QString::fromStdString(fmt::format("{}", index)));
}

void XBOFSWinQT5GUI::handleVigEmError(const std::wstring &devicePath) {
    // TODO: Note error output in text area

}

void XBOFSWinQT5GUI::handleWinUsbDeviceOpen(const std::wstring &devicePath) {
}

void XBOFSWinQT5GUI::handleWinUsbDeviceInfo(const std::wstring &devicePath, quint16 vendorId, quint16 productId,
                                            const std::wstring &manufacturer, const std::wstring &product, const std::wstring &serialNumber) {
    auto optionalIterator = getIteratorForDevicePath(devicePath);
    if (!optionalIterator) return;
    auto iterator = (*optionalIterator).second;
    auto tabWidgetUi = std::get<2>(*iterator);
    tabWidgetUi->vendorIdLabel->setText(QString::fromStdString(fmt::format("0x{:04X}", vendorId)));
    tabWidgetUi->productIdLabel->setText(QString::fromStdString(fmt::format("0x{:04X}", productId)));
    tabWidgetUi->manufacturerLabel->setText(QString::fromStdWString(manufacturer));
    tabWidgetUi->productLabel->setText(QString::fromStdWString(product));
    tabWidgetUi->serialNumberLabel->setText(QString::fromStdWString(serialNumber));    
}

void XBOFSWinQT5GUI::handleWinUsbDeviceOpened(const std::wstring &devicePath) {
}

void XBOFSWinQT5GUI::handleWinUsbDeviceInit(const std::wstring &devicePath) {
}

void XBOFSWinQT5GUI::handleWinUsbDeviceInitComplete(const std::wstring &devicePath) {
}

void XBOFSWinQT5GUI::handleWinUsbDeviceReadingInput(const std::wstring &devicePath) {
    auto optionalIterator = getIteratorForDevicePath(devicePath);
    if (!optionalIterator) return;
    auto iterator = (*optionalIterator).second;
    auto tabWidgetUi = std::get<2>(*iterator);
    tabWidgetUi->winUsbDeviceStatus->setText(QString::fromUtf8("Reading input..."));
}

void XBOFSWinQT5GUI::handleWinUsbDeviceTerminating(const std::wstring &devicePath) {
}

void XBOFSWinQT5GUI::handleWinUsbDeviceError(const std::wstring &devicePath) { 
    // TODO: Note error output in text area
}

void XBOFSWinQT5GUI::handleWinUsbDeviceManagerScanning() {
    ui.xbofsWinDeviceManagerStatus->setText(QString::fromWCharArray(LR"""(<span style="color:#2ECC40">Scanning for supported controllers...</span>)"""));
}

void XBOFSWinQT5GUI::handleTerminateWinUsbDeviceManager() {    
    logger->info("Requesting interruption of thread handling WinUsbDeviceManager");
    winUsbDeviceManagerThread->requestInterruption();
    logger->info("Signalling thread handling WinUsbDeviceManager to quit");
    winUsbDeviceManagerThread->quit();
    logger->info("Waiting for thread hanlding WinUsbDeviceManager to quit");
    winUsbDeviceManagerThread->wait();
    delete winUsbDeviceManagerThread;
    logger->flush();
}

void XBOFSWinQT5GUI::handleSystemTrayMenuRestore(const bool &checked) {
    setWindowFlags(previousFlags);
    showNormal();
}


void XBOFSWinQT5GUI::handleSystemTrayMenuExit(const bool &checked) {                
    systemTrayIconEnabled = false;              
    QApplication::quit();
}

void XBOFSWinQT5GUI::closeEvent(QCloseEvent *event) {
    if (systemTrayIconEnabled && minimizeOnClose) {        
        hide();
        event->ignore();
    }
    else handleSystemTrayMenuExit(true);
}

void XBOFSWinQT5GUI::hideEvent(QHideEvent *event) {    
    if (systemTrayIconEnabled && minimizeToTray) {
        systemTrayIcon->show();
        previousFlags = windowFlags();
        setWindowFlags(Qt::ToolTip);
    }
}

void XBOFSWinQT5GUI::showEvent(QShowEvent *event) {
    if (systemTrayIconEnabled) {
        systemTrayIcon->hide();        
    }
}

void XBOFSWinQT5GUI::handleAutostartCheckboxStateChanged(const quint16 state) {
    autostart = state == Qt::Checked;
    settings->setValue(SETTINGS_AUTOSTART, autostart);    
    auto applicationFilePath = QApplication::applicationFilePath();
    auto applicationsLocation = QStandardPaths::writableLocation(QStandardPaths::ApplicationsLocation);
    auto linkPath = applicationsLocation + QDir::separator() + "Startup" + QDir::separator() + "XBOFS.win.qt5.lnk";
    if (autostart) QFile::link(applicationFilePath, linkPath);
    else QFile::remove(linkPath);
}

void XBOFSWinQT5GUI::handleStartMinimizedCheckboxStateChanged(const quint16 state) {
    startMinimized = state == Qt::Checked;
    settings->setValue(SETTINGS_START_MINIMIZED, startMinimized);
}

void XBOFSWinQT5GUI::handleMinimizeOnCloseCheckboxStateChanged(const quint16 state) {
    minimizeOnClose = state == Qt::Checked;
    settings->setValue(SETTINGS_MINIMIZE_ON_CLOSE, minimizeOnClose);
}

void XBOFSWinQT5GUI::handleMinimizeToTrayCheckboStateChanged(const quint16 state) {
    minimizeToTray = state == Qt::Checked;
    settings->setValue(SETTINGS_MINIMIZE_TO_TRAY, minimizeToTray);
}

void XBOFSWinQT5GUI::handleUpdateCheckCheckboxStateChanged(const quint16 state) {
    checkForUpdates = state == Qt::Checked;
    settings->setValue(SETTINGS_CHECK_FOR_UPDATES, checkForUpdates);
}

void XBOFSWinQT5GUI::handleUpdateCheckResponse(QNetworkReply *response) {
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