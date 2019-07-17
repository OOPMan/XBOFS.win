#pragma once
#include "pch.h"

#include <ViGEm/Client.h>


/*
*/
class WinUsbDevice
{
public:      
    WinUsbDevice(TCHAR* devicePath);
    ~WinUsbDevice();

    DWORD getThreadId();    
    static DWORD WINAPI staticRunEventLoop(void* Param);
    DWORD runEventLoop(void);    
    
protected:
    std::atomic_flag runEventLoopFlag       = ATOMIC_FLAG_INIT;
    bool deviceHandlesOpen                  = false;
    TCHAR* devicePath                       = NULL;
    WINUSB_INTERFACE_HANDLE winUsbHandle    = NULL;
    HANDLE                  deviceHandle    = NULL;
    RAZER_ATROX_DATA_PACKET dataPacket      = {};
    RAZER_ATROX_BUTTON_STATE buttonState    = {};
    PVIGEM_CLIENT vigEmClient               = NULL;
    PVIGEM_TARGET vigEmTarget               = NULL;
    DWORD threadId                          = 0;
    HANDLE threadHandle                     = NULL;
    el::Logger* logger                      = el::Loggers::getLogger("WinUsbDevice");
    UCHAR RAZER_ATROX_INIT[5]               = { 0x05, 0x20, 0x08, 0x01, 0x05 };
    
    bool openDevice();
    bool closeDevice();    

    bool initRazorAtrox();
    bool readInputFromRazerAtrox();

    RAZER_ATROX_PACKET_TYPES processInputFromRazerAtrox();
    bool dispatchInputToVigEmController();
    
private:
};

