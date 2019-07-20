#pragma once
#include "pch.h"

#include <ViGEm/Client.h>


/*
*/
class WinUsbDevice
{
public:      
    WinUsbDevice(tstring devicePath);
    ~WinUsbDevice();

    DWORD getThreadId();    
    static DWORD WINAPI staticRunEventLoop(void* Param);
    DWORD runEventLoop(void);    
    
protected:
    std::atomic_flag runEventLoopFlag       = ATOMIC_FLAG_INIT;
    bool deviceHandlesOpen                  = false;
    tstring devicePath;
    WINUSB_INTERFACE_HANDLE winUsbHandle;
    HANDLE                  deviceHandle;
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

