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
    mvprintw(6, 0, "* W to reset WinUSB connection to Razer Atrox");
    mvprintw(7, 0, "* V to reset VigEm XB360 controller");
    mvprintw(8, 0, "* Q to exit");
    refresh();
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

LONG __cdecl _tmain(LONG Argc, LPTSTR *Argv) {
    // Variables
    WINDOW *window;
    STATUS winUsbStatus = DISCONNECTED;
    STATUS vigEmStatus = DISCONNECTED;
    DEVICE_DATA winUsbDeviceData{};

    // Init
    window = initscr();
    nodelay(window, TRUE);
    noecho();

    // Main loop
    while (true) {
        switch (winUsbStatus) {
        case DISCONNECTED: winUsbStatus = initDevice(winUsbDeviceData) ? INIT : DISCONNECTED; break;
        case INIT: winUsbStatus = initRazorAtrox(winUsbDeviceData) ? CONNECTED : DISCONNECTED; break;
        case CONNECTED: break;
        }        
        renderUI(winUsbStatus, vigEmStatus);
        auto key = getch();
        if (key == 'Q' || key == 'q') break;
    }
    
    endwin();
}
