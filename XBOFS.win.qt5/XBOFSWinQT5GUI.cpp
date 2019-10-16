#include "XBOFSWinQT5GUI.h"
#include <vector>
#include <spdlog/sinks/null_sink.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include <qthread.h>
#include <fmt/core.h>
#include <XBOFS.win/utils.h>
#include <XBOFS.win/WinUsbDeviceManager.h>

XBOFSWinQT5GUI::XBOFSWinQT5GUI(QWidget *parent)
: QMainWindow(parent)
{
    ui.setupUi(this);      
    // Configure logging
    auto sinks = std::vector<spdlog::sink_ptr>();    
    auto rotatingFileSink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>("xbofs.win.qt5.log", 1024 * 1024 * 10, 10);
    sinks.push_back(rotatingFileSink);
    logger = XBOFSWin::get_logger("XBOFSWin QT5 GUI", sinks);
    spdlog::set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%t] [%n] [%l] %v");
    logger->info("Logging initialised");
    // Start WinUsbDeviceManager    
    winUsbDeviceManagerThread = new QThread();
    winUsbDeviceManager = new XBOFSWin::WinUsbDeviceManager(XBOFSWin::get_logger("WinUsbDeviceManager", sinks));
    connect(winUsbDeviceManagerThread, &QThread::finished, winUsbDeviceManager, &QObject::deleteLater);
    connect(winUsbDeviceManagerThread, &QThread::started, winUsbDeviceManager, &XBOFSWin::WinUsbDeviceManager::run);
    connect(winUsbDeviceManager, &XBOFSWin::WinUsbDeviceManager::winUsbDeviceManagerScanning, this, &XBOFSWinQT5GUI::winUsbDeviceManagerScanning);
    connect(winUsbDeviceManager, &XBOFSWin::WinUsbDeviceManager::winUsbDeviceAdded, this, &XBOFSWinQT5GUI::winUsbDeviceAdded);
    connect(winUsbDeviceManager, &XBOFSWin::WinUsbDeviceManager::winUsbDeviceRemoved, this, &XBOFSWinQT5GUI::winUsbDeviceRemoved);
    connect(this, &XBOFSWinQT5GUI::destroyed, this, &XBOFSWinQT5GUI::terminateWinUsbDeviceManager);
    winUsbDeviceManager->moveToThread(winUsbDeviceManagerThread);
    winUsbDeviceManagerThread->start();      
}

void XBOFSWinQT5GUI::winUsbDeviceAdded(const QString &devicePath, const XBOFSWin::WinUsbDevice *winUsbDevice) {        
    // TODO: Connect signals
    // TODO: Update UI    
    auto tabWidget = new QWidget();
    auto tabWidgetUi = new Ui::WinUsbDeviceWidget();
    tabWidget->setObjectName(devicePath);
    tabWidgetUi->setupUi(tabWidget);    
    auto tabIndex = ui.tabWidget->addTab(tabWidget, QString());    
    ui.tabWidget->setTabText(tabIndex, QString::fromStdWString(fmt::format(L"Stick {}", tabIndex)));
    devicePathTabMap.insert({ devicePath, std::make_tuple(tabIndex, tabWidget, tabWidgetUi) });
}

void XBOFSWinQT5GUI::winUsbDeviceRemoved(const QString &devicePath, const XBOFSWin::WinUsbDevice *winUsbDevice) {
    // TODO: Update UI
    auto tuple = devicePathTabMap.at(devicePath);
    ui.tabWidget->removeTab(std::get<0>(tuple));
    devicePathTabMap.erase(devicePath);
}

void XBOFSWinQT5GUI::winUsbDeviceManagerScanning() {
    ui.winUsbDeviceManagerStatus->setText(QString::fromUtf8("Scanning for supported controllers..."));
}

void XBOFSWinQT5GUI::terminateWinUsbDeviceManager() {    
    logger->info("Requesting interruption of thread handling WinUsbDeviceManager");
    winUsbDeviceManagerThread->requestInterruption();
    logger->info("Signalling thread handling WinUsbDeviceManager to terminate");
    winUsbDeviceManagerThread->terminate();
    logger->info("Waiting for thread hanlding WinUsbDeviceManager to terminate");
    winUsbDeviceManagerThread->wait();
    logger->flush();
}