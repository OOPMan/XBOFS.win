#include "pch.h"

#include <stdio.h>
#include <curses.h>
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

char* statusToString(STATUS status) {
    switch (status) {
    case DISCONNECTED: return "DISCONNECTED";    
    case INIT: return "INIT";
    case CONNECTED: return "CONNECTED";
    }
    return "UNKNOWN";
}

/*
Render the PDCurses UI
*/
void renderUI(STATUS winUsbStatus, STATUS vigEmStatus) {
    erase();
    mvprintw(0, 0, "Razer Atrox WinUSB VigEm Feeder");
    mvprintw(2, 0, "WinUSB Status: %s", statusToString(winUsbStatus));
    mvprintw(3, 0, "VigEm Status: %s", statusToString(vigEmStatus));
    mvprintw(5, 0, "Press:");
    mvprintw(6, 0, "* Q and then a button on the controller to exit");
    refresh();
}

/*
Process data read from Razer Atrox
*/
RAZER_ATROX_PACKET_TYPES processInputFromRazerAtrox(RAZER_ATROX_DATA_PACKET &dataPacket, RAZER_ATROX_BUTTON_STATE &buttonState) {
    if (dataPacket.transferred == 0) return UNKNOWN;
    switch (dataPacket.data[0]) {
    case 0x01: // Dummy packet?
        return DUMMY;
    case 0x03: // Heartbeat packet?
        return HEARTBEAT;
    case 0x07: // Guide button
        buttonState.buttonGuide = dataPacket.data[4] & 0x01;
        return GUIDE;
    case 0x20: // Inputs
        buttonState.buttonA = dataPacket.data[22] & 0x10;
        buttonState.buttonB = dataPacket.data[22] & 0x20;
        buttonState.buttonX = dataPacket.data[22] & 0x01;
        buttonState.buttonY = dataPacket.data[22] & 0x02;
        buttonState.rightButton = dataPacket.data[22] & 0x04;
        buttonState.leftButton = dataPacket.data[22] & 0x08;
        buttonState.rightTrigger = dataPacket.data[22] & 0x40;
        buttonState.leftTrigger = dataPacket.data[22] & 0x80;
        buttonState.buttonMenu = dataPacket.data[04] & 0x04;
        buttonState.buttonView = dataPacket.data[04] & 0x08;
        buttonState.stickUp = dataPacket.data[05] & 0x01;
        buttonState.stickDown = dataPacket.data[05] & 0x02;
        buttonState.stickLeft = dataPacket.data[05] & 0x04;
        buttonState.stickRight = dataPacket.data[05] & 0x08;
        return BUTTON_INPUT;
    }
    return UNKNOWN;
}

/*
Blocking data read from end-point 0x81
*/
bool readInputFromRazerAtrox(DEVICE_DATA &winUsbDeviceData, RAZER_ATROX_DATA_PACKET &dataPacket)
{
    if (winUsbDeviceData.WinusbHandle == INVALID_HANDLE_VALUE) return false;
    return WinUsb_ReadPipe(winUsbDeviceData.WinusbHandle, 0x81, dataPacket.data, 30, &dataPacket.transferred, NULL);    
}

/*
Sent the INIT packet to the Razor Atrox
*/
bool initRazorAtrox(DEVICE_DATA &winUsbDeviceData) {
    if (winUsbDeviceData.WinusbHandle == INVALID_HANDLE_VALUE) return false;   
    ULONG cbSent = 0;    
    return WinUsb_WritePipe(winUsbDeviceData.WinusbHandle, 0x01, RAZER_ATROX_INIT, 5, &cbSent, 0);
}

/*
Initialize the WinUSB device
*/
bool initDevice(DEVICE_DATA &winUsbDeviceData) {
    BOOL noWinUsbDevice;
    BOOL winUsbGetDescriptorResult;
    USB_DEVICE_DESCRIPTOR winUsbDeviceDescriptor;
    ULONG bytesReceived;    
    HRESULT openWinUsbDeviceResult = OpenDevice(&winUsbDeviceData, &noWinUsbDevice);
    if (FAILED(openWinUsbDeviceResult)) return false;     
    winUsbGetDescriptorResult = WinUsb_GetDescriptor(
        winUsbDeviceData.WinusbHandle, USB_DEVICE_DESCRIPTOR_TYPE, 0, 0, (PBYTE)&winUsbDeviceDescriptor, sizeof(winUsbDeviceDescriptor), &bytesReceived
    );
    if (winUsbGetDescriptorResult == FALSE || bytesReceived != sizeof(winUsbDeviceDescriptor)) {
        CloseDevice(&winUsbDeviceData);
        return false;
    }
    return true;
}

/*
Dispatch data to the VigEm XB360 controller
*/
bool dispatchInputToVigEmController(PVIGEM_CLIENT vigEmClient, PVIGEM_TARGET vigEmController, RAZER_ATROX_BUTTON_STATE &buttonState) {
    XUSB_REPORT controllerData{};
    if (buttonState.buttonGuide)    controllerData.wButtons |= XUSB_GAMEPAD_GUIDE;
    if (buttonState.buttonMenu)     controllerData.wButtons |= XUSB_GAMEPAD_START;
    if (buttonState.buttonView)     controllerData.wButtons |= XUSB_GAMEPAD_BACK;
    if (buttonState.buttonA)        controllerData.wButtons |= XUSB_GAMEPAD_A;
    if (buttonState.buttonB)        controllerData.wButtons |= XUSB_GAMEPAD_B;
    if (buttonState.buttonX)        controllerData.wButtons |= XUSB_GAMEPAD_X;
    if (buttonState.buttonY)        controllerData.wButtons |= XUSB_GAMEPAD_Y;
    if (buttonState.leftButton)     controllerData.wButtons |= XUSB_GAMEPAD_LEFT_SHOULDER;
    if (buttonState.rightButton)    controllerData.wButtons |= XUSB_GAMEPAD_RIGHT_SHOULDER;
    if (buttonState.stickUp)        controllerData.wButtons |= XUSB_GAMEPAD_DPAD_UP;
    if (buttonState.stickDown)      controllerData.wButtons |= XUSB_GAMEPAD_DPAD_DOWN;
    if (buttonState.stickLeft)      controllerData.wButtons |= XUSB_GAMEPAD_DPAD_LEFT;
    if (buttonState.stickRight)     controllerData.wButtons |= XUSB_GAMEPAD_DPAD_RIGHT;
    if (buttonState.leftTrigger)    controllerData.bLeftTrigger = 0xff;
    if (buttonState.rightTrigger)   controllerData.bRightTrigger = 0xff;
    const auto controllerUpdateResult = vigem_target_x360_update(vigEmClient, vigEmController, controllerData);
    return VIGEM_SUCCESS(controllerUpdateResult);
}

LONG __cdecl _tmain(LONG Argc, LPTSTR *Argv) {
    // Variables
    WINDOW *window;
    STATUS winUsbStatus = DISCONNECTED;
    STATUS vigEmStatus = DISCONNECTED;
    DEVICE_DATA winUsbDeviceData{};
    RAZER_ATROX_DATA_PACKET razerAtroxDataPacket{};
    RAZER_ATROX_BUTTON_STATE  razerAtroxButtonState{};
    int failedReads = 0;
    PVIGEM_CLIENT vigEmClient = vigem_alloc();
    PVIGEM_TARGET vigEmController = vigem_target_x360_alloc();
    int failedWrites = 0;

    // Init        
    window = initscr();
    nodelay(window, TRUE);
    noecho();

    // Main loop
    while (true) {
        // Process WinUSB component
        switch (winUsbStatus) {
        case DISCONNECTED: winUsbStatus = initDevice(winUsbDeviceData) ? INIT : DISCONNECTED; break;
        case INIT: winUsbStatus = initRazorAtrox(winUsbDeviceData) ? CONNECTED : DISCONNECTED; break;
        case CONNECTED: failedReads += readInputFromRazerAtrox(winUsbDeviceData, razerAtroxDataPacket) ? 0 : 1;
        }        
        // Process button state
        processInputFromRazerAtrox(razerAtroxDataPacket, razerAtroxButtonState);
        // Process VigEm component
        switch (vigEmStatus) {
        case DISCONNECTED:
            vigEmStatus = VIGEM_SUCCESS(vigem_connect(vigEmClient)) ? INIT : DISCONNECTED;
            break;
        case INIT: 
            vigEmStatus = VIGEM_SUCCESS(vigem_target_add(vigEmClient, vigEmController)) ? CONNECTED : INIT;
            break;            
        case CONNECTED: failedWrites += dispatchInputToVigEmController(vigEmClient, vigEmController, razerAtroxButtonState) ? 0 : 1; break;
        }
        // Check to see if we've hit the failed read threshold
        if (failedReads > 5) {
            failedReads = 0;
            CloseDevice(&winUsbDeviceData);            
            winUsbStatus = DISCONNECTED;
        }
        // TODO: Handle failed writes
        // Render UI
        renderUI(winUsbStatus, vigEmStatus);
        auto key = getch();
        if (key == 'Q' || key == 'q') break;
    }
    // TODO: Safety!
    CloseDevice(&winUsbDeviceData);
    vigem_target_remove(vigEmClient, vigEmController);
    vigem_disconnect(vigEmClient);
    vigem_free(vigEmClient);
    endwin();
}
