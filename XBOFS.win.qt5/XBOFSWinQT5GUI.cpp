#include "XBOFSWinQT5GUI.h"
#include <vector>

XBOFSWinQT5GUI::XBOFSWinQT5GUI(QWidget *parent)
: QMainWindow(parent)
{
    ui.setupUi(this);  
    DWORD threadId = GetCurrentThreadId();    
    this->logger = XBOFSWin::setup_logger("test", "test.log", std::vector<spdlog::sink_ptr>());
    this->winUsbDeviceManager = new XBOFSWin::WinUsbDeviceManager(this->logger, threadId, threadId);
}
