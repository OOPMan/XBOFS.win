#include "WinUsbDeviceManager.h"

#include <cfgmgr32.h>
#include <string.h>

#ifdef UNICODE
#define SecureStrTok strtok_s
#else
#define SecureStrTok wcstok_s
#endif

WinUsbDeviceManager::WinUsbDeviceManager()
{
    this->devicePathWinUsbDeviceMap.insert_or_assign(TEXT("HELLO"), new WinUsbDevice());    
}


WinUsbDeviceManager::~WinUsbDeviceManager()
{
}

DWORD WINAPI WinUsbDeviceManager::StaticThreadStart(void * Param) {
    WinUsbDeviceManager* This = (WinUsbDeviceManager*)Param;
    return This->ThreadStart();
}

DWORD WinUsbDeviceManager::ThreadStart(void) {

}

void WinUsbDeviceManager::startMyThread() {
    DWORD ThreadID;
    CreateThread(NULL, 0, StaticThreadStart, (void*)this, 0, &ThreadID);
}

/*
Retrieve a vector of TCHAR representing device paths that the device manager will work with
*/
std::vector<TCHAR*> WinUsbDeviceManager::retrieveDevicePaths() {
    CONFIGRET cr = CR_SUCCESS;
    HRESULT   hr = S_OK;
    PTSTR     DeviceInterfaceList = NULL;
    ULONG     DeviceInterfaceListLength = 0;    
    //
    // Enumerate all devices exposing the interface. Do this in a loop
    // in case a new interface is discovered while this code is executing,
    // causing CM_Get_Device_Interface_List to return CR_BUFFER_SMALL.
    //
    do {
        cr = CM_Get_Device_Interface_List_Size(&DeviceInterfaceListLength,
            (LPGUID)&GUID_DEVINTERFACE_RazorAtroxWinUSBVigEmFeeder,
            NULL,
            CM_GET_DEVICE_INTERFACE_LIST_PRESENT);

        if (cr != CR_SUCCESS) {
            hr = HRESULT_FROM_WIN32(CM_MapCrToWin32Err(cr, ERROR_INVALID_DATA));
            break;
        }

        DeviceInterfaceList = (PTSTR)HeapAlloc(GetProcessHeap(),
            HEAP_ZERO_MEMORY,
            DeviceInterfaceListLength * sizeof(TCHAR));

        if (DeviceInterfaceList == NULL) {
            hr = E_OUTOFMEMORY;
            break;
        }

        cr = CM_Get_Device_Interface_List((LPGUID)&GUID_DEVINTERFACE_RazorAtroxWinUSBVigEmFeeder,
            NULL,
            DeviceInterfaceList,
            DeviceInterfaceListLength,
            CM_GET_DEVICE_INTERFACE_LIST_PRESENT);

        if (cr != CR_SUCCESS) {
            HeapFree(GetProcessHeap(), 0, DeviceInterfaceList);

            if (cr != CR_BUFFER_SMALL) {
                hr = HRESULT_FROM_WIN32(CM_MapCrToWin32Err(cr, ERROR_INVALID_DATA));
            }
        }
    } while (cr == CR_BUFFER_SMALL);

    std::vector<TCHAR*> devicePaths;
    // See https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/strtok-s-strtok-s-l-wcstok-s-wcstok-s-l-mbstok-s-mbstok-s-l?view=vs-2017
    TCHAR *next_token = NULL;
    TCHAR *token = NULL;
    const TCHAR separator = TEXT('\0');
    token = _tcstok_s(DeviceInterfaceList, separator, &next_token);
    while (token != NULL) {
        // TODO: Add to vector
        devicePaths.push_back(token);
        token = _tcstok_s(DeviceInterfaceList, separator, &next_token);
        
    }
    HeapFree(GetProcessHeap(), 0, DeviceInterfaceList);
    return devicePaths;
}