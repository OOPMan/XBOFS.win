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
    RAWUVEF_STOP = WM_USER + 0
};
