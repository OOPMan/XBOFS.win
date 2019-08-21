#pragma once
#include "pch.h"

namespace XBOFSWin {

    enum THREAD_MESSAGES {
        RAWUVEF_STOP = WM_USER + 0,
        RAWUVEF_STOPPED = WM_USER + 1,
        RAWUVEF_WIN_USB_DEVICE_MANAGER_STARTED = WM_USER + 2,
        RAWUVEF_WIN_USB_DEVICE_MANAGER_SCANNING = WM_USER + 3,
        RAWUVEF_WIN_USB_DEVICE_MANAGER_SLEEPING = WM_USER + 4,
        RAWUVEF_WIN_USB_DEVICE_MANAGER_TERMINATING = WM_USER + 5,
        RAWUVEF_WIN_USB_DEVICE_MANAGER_ERROR = WM_USER + 6,
        RAWUVEF_WIN_USB_DEVICE_STARTED = WM_USER + 7,
        RAWUVEF_WIN_USB_DEVICE_VIGEM_CONNECT = WM_USER + 8,
        RAWUVEF_WIN_USB_DEVICE_VIGEM_TARGET_ADD = WM_USER + 9,
        RAWUVEF_WIN_USB_DEVICE_OPEN = WM_USER + 10,
        RAWUVEF_WIN_USB_DEVICE_INIT = WM_USER + 11,
        RAWUVEF_WIN_USB_DEVICE_READ_INPUT = WM_USER + 12,
        RAWUVEF_WIN_USB_DEVICE_TERMINATING = WM_USER + 13,
        RAWUVEF_WIN_USB_DEVICE_ERROR = WM_USER + 14
    };

    std::string threadMessageToString(THREAD_MESSAGES threadMessage);

    class Thread
    {
    public:
        Thread() = delete;
        Thread(std::string identifier, std::shared_ptr<spdlog::logger> logger, DWORD parentThreadId, DWORD uiManagerThreadId);
        ~Thread();

        virtual DWORD run() = 0;
        DWORD getThreadId();
        DWORD getParentThreadId();
        DWORD getUiManagerThreadId();

    protected:
        const std::string identifier;
        const DWORD parentThreadId;
        const DWORD uiManagerThreadId;

        std::shared_ptr<spdlog::logger> logger;
        DWORD threadId = 0;
        HANDLE threadHandle = NULL;

        static DWORD startThread(LPVOID data);
        BOOL notifyUIManager(UINT messageValue, LPARAM lParam);
    };
}
