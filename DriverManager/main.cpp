#include "DriverManager.h"
#include <QtWidgets/QApplication>

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
    SingleInstanceLimiter limiter(TEXT("Global\\{58f8ed20-bc18-4523-9ec2-cd6e06f56767}"));
    if (!limiter.isAnotherInstanceRunning()) {
        DriverManager mainWindow;
        mainWindow.show();
        return application.exec();
    }
    return -1;
}
