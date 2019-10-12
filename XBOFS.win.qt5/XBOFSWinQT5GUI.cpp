#include "XBOFSWinQT5GUI.h"
#include <vector>
#include <spdlog/sinks/null_sink.h>
#include <qthread.h>
#include <XBOFS.win/utils.h>
#include <XBOFS.win/WinUsbDeviceManager.h>

XBOFSWinQT5GUI::XBOFSWinQT5GUI(QWidget *parent)
: QMainWindow(parent)
{
    ui.setupUi(this);  
    DWORD threadId = GetCurrentThreadId();    
    auto sinks = std::vector<spdlog::sink_ptr>();    
    this->logger = XBOFSWin::setup_logger("test", "xbofs.win.log", sinks);
    auto winUsbDeviceManagerThread = new QThread();
    auto winUsbDeviceManager = new XBOFSWin::WinUsbDeviceManager("WinUsbDeviceManager", this->logger);
    connect(winUsbDeviceManagerThread, &QThread::finished, winUsbDeviceManager, &QObject::deleteLater);
    connect(winUsbDeviceManagerThread, &QThread::started, winUsbDeviceManager, &XBOFSWin::WinUsbDeviceManager::run);
    winUsbDeviceManager->moveToThread(winUsbDeviceManagerThread);
    winUsbDeviceManagerThread->start();      
}
