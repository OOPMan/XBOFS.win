#include "XBOFSWinQT5GUI.h"
#include <vector>
#include <spdlog/sinks/null_sink.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include <qthread.h>
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
    logger = XBOFSWin::setup_logger("WinUsbDeviceManager", "", sinks);    
    spdlog::set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%t] [%n] [%l] %v");
    logger->info("Logging initialised");
    // Start WinUsbDeviceManager
    winUsbDeviceManagerThread = new QThread();
    winUsbDeviceManager = new XBOFSWin::WinUsbDeviceManager("WinUsbDeviceManager", logger);
    connect(winUsbDeviceManagerThread, &QThread::finished, winUsbDeviceManager, &QObject::deleteLater);
    connect(winUsbDeviceManagerThread, &QThread::started, winUsbDeviceManager, &XBOFSWin::WinUsbDeviceManager::run);
    connect(winUsbDeviceManager, &XBOFSWin::WinUsbDeviceManager::winUsbDeviceManagerScanning, this, &XBOFSWinQT5GUI::winUsbDeviceManagerScanning);
    connect(winUsbDeviceManager, &XBOFSWin::WinUsbDeviceManager::winUsbDeviceAdded, this, &XBOFSWinQT5GUI::winUsbDeviceAdded);
    connect(winUsbDeviceManager, &XBOFSWin::WinUsbDeviceManager::winUsbDeviceRemoved, this, &XBOFSWinQT5GUI::winUsbDeviceRemoved);
    connect(this, &XBOFSWinQT5GUI::destroyed, this, &XBOFSWinQT5GUI::terminateWinUsbDeviceManager);
    winUsbDeviceManager->moveToThread(winUsbDeviceManagerThread);
    winUsbDeviceManagerThread->start();      
}

void XBOFSWinQT5GUI::winUsbDeviceAdded(const QString &identifier, const XBOFSWin::WinUsbDevice &winUsbDevice) {
    // TODO: Connect signals
    // TODO: Update UI
}

void XBOFSWinQT5GUI::winUsbDeviceRemoved(const QString &identifierr, const XBOFSWin::WinUsbDevice &winUsbDevice) {
    // TODO: Update UI
}

void XBOFSWinQT5GUI::winUsbDeviceManagerScanning() {
    ui.winUsbDeviceManagerStatus->setText(QString::fromUtf8("Scanning for supported controllers..."));
}

void XBOFSWinQT5GUI::terminateWinUsbDeviceManager() {
    auto identifier = "WinUsbDeviceManager";
    logger->info("Requesting interruption of thread handling {}", identifier);
    winUsbDeviceManagerThread->requestInterruption();
    logger->info("Signalling thread handling {} to terminate", identifier);
    winUsbDeviceManagerThread->terminate();
    this->logger->info("Waiting for thread hanlding {} to terminate", identifier);
    winUsbDeviceManagerThread->wait();
    logger->flush();
}