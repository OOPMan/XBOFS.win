#include <string>
#include <qapplication.h>
#include <qmessagebox.h>
#include <qmetatype.h>
#include <spdlog/sinks/rotating_file_sink.h>

#include "XBOFSWinQTGUI.h"

/*
* Single instance limiting function from https://www.qtcentre.org/threads/14079-How-to-detect-that-first-instance-of-application-is-already-running
*/
class SingleInstanceLimiter
{
protected:
    DWORD  m_dwLastError;
    HANDLE m_hMutex;

public:
    SingleInstanceLimiter(TCHAR* strMutexName)
    {
        //Make sure that you use a name that is unique for this application otherwise
        //two apps may think they are the same if they are using same name for
        //3rd parm to CreateMutex
        m_hMutex = CreateMutex(NULL, FALSE, strMutexName); //do early
        m_dwLastError = GetLastError(); //save for use later...
    }

    ~SingleInstanceLimiter()
    {
        if (m_hMutex)  //Do not forget to close handles.
        {
            CloseHandle(m_hMutex); //Do as late as possible.
            m_hMutex = NULL; //Good habit to be in.
        }
    }

    BOOL isAnotherInstanceRunning()
    {
        return (ERROR_ALREADY_EXISTS == m_dwLastError);
    }
};

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);
    SingleInstanceLimiter limiter(TEXT("Global\\{74cbcbe6-4202-4a85-9362-ae371291abd6}"));
    qRegisterMetaType<std::wstring>();
    // Configure logging
    spdlog::set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%t] [%n] [%l] %v");
    spdlog::flush_every(std::chrono::seconds(1));
    auto rotatingFileSink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>("xbofs.win.qt5.log", 1024 * 1024 * 10, 10);
    auto sinks = std::vector<spdlog::sink_ptr>{ rotatingFileSink };
    auto logger = XBOFSWin::get_logger("XBOFS.Win", sinks);
    logger->info("Logging initialised");
    // Display main window
    int result = -1;
    if (!limiter.isAnotherInstanceRunning()) {
        XBOFSWinQTGUI mainWindow(XBOFSWin::get_logger("XBOFSWinQTGUI", logger->sinks()));
        result = application.exec();
    }
    else {
        logger->error("Another instance of XBOFS.win is already running");
    }
    logger->info("Application exit");
    return result;
}

