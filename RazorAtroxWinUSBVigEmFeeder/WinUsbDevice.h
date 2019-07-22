#pragma once
#include "pch.h"

#include <ViGEm/Client.h>


/*
*/
class WinUsbDevice
{
public:      
    WinUsbDevice(tstring devicePath, DWORD parentThreadId, DWORD uiManagerThreadId);
    ~WinUsbDevice();

    DWORD getThreadId();    
    static DWORD WINAPI staticRunEventLoop(void* Param);
    DWORD runEventLoop(void);    
    
protected:
    std::atomic_flag runEventLoopFlag       = ATOMIC_FLAG_INIT;
    DWORD parentThreadId                    = 0;
    DWORD uiManagerThreadId                 = 0;
    DWORD threadId                          = 0;
    HANDLE threadHandle                     = NULL;
    el::Logger* logger                      = el::Loggers::getLogger("WinUsbDevice");
    tstring devicePath;
    bool deviceHandlesOpen                  = false;        
    UCHAR RAZER_ATROX_INIT[5]               = { 0x05, 0x20, 0x08, 0x01, 0x05 };
    RAZER_ATROX_DATA_PACKET dataPacket      = {};
    RAZER_ATROX_BUTTON_STATE buttonState    = {};
    PVIGEM_CLIENT vigEmClient               = NULL;
    PVIGEM_TARGET vigEmTarget               = NULL;       
    WINUSB_INTERFACE_HANDLE winUsbHandle;
    HANDLE deviceHandle;
    
    bool openDevice();
    bool closeDevice();    
    bool initRazorAtrox();
    bool readInputFromRazerAtrox();
    RAZER_ATROX_PACKET_TYPES processInputFromRazerAtrox();
    bool dispatchInputToVigEmController();
    
private:
};

