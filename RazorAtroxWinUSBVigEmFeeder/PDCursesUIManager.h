#pragma once
#include "pch.h"
#include "thread.h"
#include "WinUsbDeviceManager.h"

#include <curses.h>

class PDCursesUIManager : public Thread
{
public:
    PDCursesUIManager(DWORD parentThreadId);
    ~PDCursesUIManager() {};

    DWORD run();
    void wait();
protected:
    WINDOW *window;
    WinUsbDeviceManager *winUsbDeviceManager;    
};

