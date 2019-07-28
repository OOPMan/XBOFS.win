#include "PDCursesUIManager.h"

PDCursesUIManager::PDCursesUIManager(DWORD parentThreadId) 
: Thread("PDCursesUIManager", "PDCursesUIManager", parentThreadId, parentThreadId)
{
}

void PDCursesUIManager::wait()
{
    WaitForSingleObject(this->threadHandle, INFINITE);
}

DWORD PDCursesUIManager::run() 
{
    MSG threadMessage;
    bool loop = true;
    window = initscr();
    //nodelay(window, TRUE);
    noecho();
    this->winUsbDeviceManager = new WinUsbDeviceManager(this->threadId, this->threadId);
    while (loop) {
        erase();
        mvprintw(0, 0, "Razer Atrox WinUSB VigEm Feeder");
        mvprintw(2, 0, "Press Q to exit");        
        refresh();
        if (PeekMessage(&threadMessage, NULL, WM_USER, WM_APP, PM_REMOVE) == TRUE && threadMessage.message == RAWUVEF_STOP) loop = false;
        auto key = getch();
        loop = (key != 'Q' && key != 'q');
    }
    erase();
    mvprintw(0, 0, "Waiting for all threads to exit...");
    refresh();
    delete this->winUsbDeviceManager;
    endwin();
    return 0;
}
