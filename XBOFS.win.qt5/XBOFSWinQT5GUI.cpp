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
    DWORD threadId = GetCurrentThreadId();    
    auto sinks = std::vector<spdlog::sink_ptr>();    
    auto rotatingFileSink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>("xbofs.win.qt5.log", 1024 * 1024 * 10, 10);
    sinks.push_back(rotatingFileSink);
    this->logger = XBOFSWin::setup_logger("WinUsbDeviceManager", "", sinks);
    spdlog::flush_every(std::chrono::seconds(60));
    spdlog::set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%t] [%n] [%l] %v");
    auto winUsbDeviceManagerThread = new QThread();
    auto winUsbDeviceManager = new XBOFSWin::WinUsbDeviceManager("WinUsbDeviceManager", this->logger);
    connect(winUsbDeviceManagerThread, &QThread::finished, winUsbDeviceManager, &QObject::deleteLater);
    connect(winUsbDeviceManagerThread, &QThread::started, winUsbDeviceManager, &XBOFSWin::WinUsbDeviceManager::run);
    winUsbDeviceManager->moveToThread(winUsbDeviceManagerThread);
    winUsbDeviceManagerThread->start();      
}
