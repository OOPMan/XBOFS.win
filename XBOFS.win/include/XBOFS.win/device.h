#pragma once
//
// Define below GUIDs
//
#include <initguid.h>
#include "stdafx.h"

//
// Device Interface GUID.
// Used by all WinUsb devices that this application talks to.
// Must match "DeviceInterfaceGUIDs" registry value specified in the INF file.
//
// 5ACF052A-3BE5-46AE-905E-356BA17671BD
DEFINE_GUID(GUID_DEVINTERFACE_XBOFS_WIN_CONTROLLER,
    0x5ACF052A, 0x3BE5, 0x46AE, 0x90, 0x5E, 0x35, 0x6B, 0xA1, 0x76, 0x71, 0xBD);

typedef struct _DEVICE_DATA {

    BOOL                    HandlesOpen;
    WINUSB_INTERFACE_HANDLE WinusbHandle;
    HANDLE                  DeviceHandle;
    TCHAR                   DevicePath[MAX_PATH];

} DEVICE_DATA, *PDEVICE_DATA;

HRESULT
OpenDevice(
    _Out_     PDEVICE_DATA DeviceData,
    _Out_opt_ PBOOL        FailureDeviceNotFound
    );

VOID
CloseDevice(
    _Inout_ PDEVICE_DATA DeviceData
    );

