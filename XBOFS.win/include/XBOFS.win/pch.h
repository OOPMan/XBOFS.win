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
#include <spdlog/logger.h>
#include <spdlog/sinks/basic_file_sink.h>

#include "device.h"
#include "utils.h"
#include "stdafx.h"

typedef std::basic_string<TCHAR> tstring;

