#include "XBOFS.win\utils.h"
#include <cfgmgr32.h>
#include <ViGEm/km/BusShared.h>

/*
See https://stackoverflow.com/a/3999597/106057
*/
std::string XBOFSWin::utf8_encode(const std::wstring &wstr)
{
    if (wstr.empty()) return std::string();
    int size_needed = WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), NULL, 0, NULL, NULL);
    std::string strTo(size_needed, 0);
    WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), &strTo[0], size_needed, NULL, NULL);
    return strTo;
}

/*
See https://stackoverflow.com/a/3999597/106057
*/
std::wstring XBOFSWin::utf8_decode(const std::string &str)
{
    if (str.empty()) return std::wstring();
    int size_needed = MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), NULL, 0);
    std::wstring wstrTo(size_needed, 0);
    MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), &wstrTo[0], size_needed);
    return wstrTo;
}

std::shared_ptr<spdlog::logger> XBOFSWin::get_logger(std::wstring loggerName, std::vector<spdlog::sink_ptr> sinks)
{
    return get_logger(utf8_encode(loggerName), sinks);
}

std::shared_ptr<spdlog::logger> XBOFSWin::get_logger(std::string loggerName, std::vector<spdlog::sink_ptr> sinks)
{
    auto logger = spdlog::get(loggerName);
    if (!logger)
    {        
        logger = std::make_shared<spdlog::logger>(loggerName, std::begin(sinks), std::end(sinks));
        spdlog::register_logger(logger);        
    }
    return logger;
}

bool XBOFSWin::deviceInterfaceAvailable(LPGUID deviceInterfaceGUID, bool present)
{
    CONFIGRET               configurationManagerResult = CR_SUCCESS;
    ULONG                   deviceInterfaceListSize = 0;
    HRESULT                 resultHandle = S_OK;
    configurationManagerResult = CM_Get_Device_Interface_List_Size(
        &deviceInterfaceListSize,
        deviceInterfaceGUID,
        NULL,
        present ? CM_GET_DEVICE_INTERFACE_LIST_PRESENT : CM_GET_DEVICE_INTERFACE_LIST_ALL_DEVICES
    );

    if (configurationManagerResult != CR_SUCCESS) return false;    
    return deviceInterfaceListSize > 1;
}

bool XBOFSWin::vigEmBusAvailable()
{
    return deviceInterfaceAvailable((LPGUID)&GUID_DEVINTERFACE_BUSENUM_VIGEM);
}

bool XBOFSWin::XBOFSWinDeviceInstalled()
{
    return deviceInterfaceAvailable((LPGUID)&GUID_DEVINTERFACE_XBOFS_WIN_CONTROLLER, false);
}