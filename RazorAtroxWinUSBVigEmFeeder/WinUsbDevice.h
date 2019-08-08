#pragma once
#include "pch.h"
#include "Thread.h"

#include <ViGEm/Client.h>


/*
*/
class WinUsbDevice : public Thread
{
public:      
    WinUsbDevice(tstring devicePath, std::string identifier, DWORD parentThreadId, DWORD uiManagerThreadId);
    ~WinUsbDevice() {};

    DWORD run(void);    
    
protected:    
    const tstring devicePath;
    
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
};
