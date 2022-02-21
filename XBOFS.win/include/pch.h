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
#include <qmetatype.h>




Q_DECLARE_METATYPE(std::wstring)