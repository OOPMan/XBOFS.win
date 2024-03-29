#pragma once
#include "pch.h"
#include "device.h"

namespace XBOFSWin {

    enum class XB360_CONTROL_BUTTONS {
        DPAD_UP,
        DPAD_DOWN,
        DPAD_LEFT,
        DPAD_RIGHT,
        X,
        Y,
        A,
        B,
        RB,
        RT,
        LB, 
        LT,
        VIEW,
        START,
        GUIDE,
        THUMB_LEFT,
        THUMB_RIGHT
    };

    std::string utf8_encode(const std::wstring &wstr);
    std::wstring utf8_decode(const std::string &str);    
    std::shared_ptr<spdlog::logger> get_logger(std::wstring loggerName, std::vector<spdlog::sink_ptr> sinks);
    std::shared_ptr<spdlog::logger> get_logger(std::string loggerName, std::vector<spdlog::sink_ptr> sinks);

    bool deviceInterfaceAvailable(LPGUID deviceInterfaceGUID, bool present=true);
    bool vigEmBusAvailable();
    bool XBOFSWinDeviceInstalled();
}