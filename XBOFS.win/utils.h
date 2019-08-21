#pragma once
#include "pch.h"

namespace XBOFSWin {

    std::string utf8_encode(const std::wstring &wstr);
    std::wstring utf8_decode(const std::string &str);
    std::shared_ptr<spdlog::logger> setup_logger(std::string loggerName, std::string logFile, std::vector<spdlog::sink_ptr> sinks);
}