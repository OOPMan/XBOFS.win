#include "WinUsbDevice.h"



WinUsbDevice::WinUsbDevice(TCHAR* devicePath)
{
    this->devicePath = devicePath;
}


WinUsbDevice::~WinUsbDevice()
{
}

DWORD WINAPI WinUsbDevice::staticRunEventLoop(void * winUsbDeviceInstance) {
    WinUsbDevice* winUsbDevice = (WinUsbDevice*)winUsbDeviceInstance;
    return winUsbDevice->runEventLoop();
}

DWORD WinUsbDevice::runEventLoop(void) {
    this->runEventLoopFlag.test_and_set();
    while (this->runEventLoopFlag.test_and_set()) {
        // TODO: Implement
    }
    return 0;
}

DWORD WinUsbDevice::getThreadId() {
    return this->threadId;
}

/*
*/
HANDLE WinUsbDevice::runEventLoopInThread() {
    return CreateThread(NULL, 0, staticRunEventLoop, (void*)this, 0, &this->threadId);
}
