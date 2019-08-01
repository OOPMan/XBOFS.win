#pragma once
#include <Windows.h>
#include <tchar.h>
#include <strsafe.h>
#include <winusb.h>
#include <usb.h>
#include <unordered_map>
#include <string>
#include <set>
#include <atomic>

#include "easylogging++.h"
#include "device.h"

typedef std::basic_string<TCHAR> tstring;

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
