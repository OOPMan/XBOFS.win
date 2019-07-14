#pragma once
#include "pch.h"

#include <ViGEm/Client.h>

UCHAR RAZER_ATROX_INIT[] = {
    0x05, 0x20, 0x08, 0x01, 0x05
};

struct RAZER_ATROX_DATA_PACKET
{
    UCHAR data[30];
    ULONG transferred;
};

struct RAZER_ATROX_BUTTON_STATE
{
    BOOL buttonX;
    BOOL buttonY;
    BOOL buttonA;
    BOOL buttonB;
    BOOL rightButton;
    BOOL leftButton;
    BOOL rightTrigger;
    BOOL leftTrigger;
    BOOL buttonMenu;
    BOOL buttonView;
    BOOL buttonGuide;
    BOOL stickUp;
    BOOL stickLeft;
    BOOL stickDown;
    BOOL stickRight;
};

enum RAZER_ATROX_PACKET_TYPES
{
    UNKNOWN,
    DUMMY,
    HEARTBEAT,
    GUIDE,
    BUTTON_INPUT
};

enum STATUS {
    DISCONNECTED,
    INIT,
    CONNECTED
};

/*
*/
class WinUsbDevice
{
public:
    std::atomic_flag runEventLoopFlag = ATOMIC_FLAG_INIT;
    

    WinUsbDevice(TCHAR* devicePath);
    ~WinUsbDevice();

    static DWORD WINAPI staticRunEventLoop(void* Param);
    DWORD getThreadId();
    HANDLE getThreadHandle();
    DWORD runEventLoop(void);
    HANDLE runEventLoopInThread();
protected:
    TCHAR* devicePath;
    DWORD threadId;
    HANDLE threadHandle = NULL;
    el::Logger* logger = el::Loggers::getLogger("WinUsbDevice");
    
    bool initDevice(DEVICE_DATA &winUsbDeviceData);
    bool initRazorAtrox(DEVICE_DATA &winUsbDeviceData);
    bool readInputFromRazerAtrox(DEVICE_DATA &winUsbDeviceData, RAZER_ATROX_DATA_PACKET &dataPacket);

    RAZER_ATROX_PACKET_TYPES processInputFromRazerAtrox(RAZER_ATROX_DATA_PACKET &dataPacket, RAZER_ATROX_BUTTON_STATE &buttonState);
    bool dispatchInputToVigEmController(PVIGEM_CLIENT vigEmClient, PVIGEM_TARGET vigEmController, RAZER_ATROX_BUTTON_STATE &buttonState);
    
private:
};

