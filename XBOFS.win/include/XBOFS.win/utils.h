#pragma once
#include <XBOFS.win/pch.h>

namespace XBOFSWin {

    std::string utf8_encode(const std::wstring &wstr);
    std::wstring utf8_decode(const std::string &str);    
    std::shared_ptr<spdlog::logger> get_logger(std::wstring loggerName, std::vector<spdlog::sink_ptr> sinks);
    std::shared_ptr<spdlog::logger> get_logger(std::string loggerName, std::vector<spdlog::sink_ptr> sinks);
}