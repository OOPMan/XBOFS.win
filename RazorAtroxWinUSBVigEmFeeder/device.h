//
// Define below GUIDs
//
#include <initguid.h>

//
// Device Interface GUID.
// Used by all WinUsb devices that this application talks to.
// Must match "DeviceInterfaceGUIDs" registry value specified in the INF file.
// 9B65FE78-9976-4E8A-A28D-6CE34BE8329D
//
DEFINE_GUID(GUID_DEVINTERFACE_RazorAtroxWinUSBVigEmFeeder,
    0x9b65fe78, 0x9976, 0x4e8a, 0xa2, 0x8d, 0x6c, 0xe3, 0x4b, 0xe8, 0x32, 0x9d);    

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
