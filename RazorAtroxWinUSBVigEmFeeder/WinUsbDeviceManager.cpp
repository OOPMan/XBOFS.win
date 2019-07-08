#include "WinUsbDeviceManager.h"

WinUsbDeviceManager::WinUsbDeviceManager()
{
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