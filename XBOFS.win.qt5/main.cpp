#include <string>
#include <qapplication.h>
#include <qmetatype.h>
#include <spdlog/sinks/rotating_file_sink.h>

#include "XBOFSWinQT5GUI.h"

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);
    qRegisterMetaType<std::wstring>();    
    // Configure logging
    spdlog::set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%t] [%n] [%l] %v");
    spdlog::flush_every(std::chrono::seconds(1));
    auto rotatingFileSink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>("xbofs.win.qt5.log", 1024 * 1024 * 10, 10);
    auto sinks = std::vector<spdlog::sink_ptr>{ rotatingFileSink };
    auto logger = XBOFSWin::get_logger("XBOFS.Win", sinks);
    logger->info("Logging initialised");
    // Display main window
    XBOFSWinQT5GUI mainWindow(XBOFSWin::get_logger("XBOFSWinQT5GUI", logger->sinks()));    
    auto result = application.exec();
    logger->info("Application exit");
    return result;
}
