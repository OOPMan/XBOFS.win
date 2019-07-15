#include "WinUsbDevice.h"

/*
Constructs the WinUsbDevice instance and starts its event loop in a separate thread
*/
WinUsbDevice::WinUsbDevice(TCHAR* devicePath)
{
    this->devicePath = devicePath;
    this->logger->info("Starting event loop for %s", devicePath);
    this->threadHandle = CreateThread(NULL, 0, staticRunEventLoop, (void*)this, 0, &this->threadId);
}

/*
Signals the event loop to terminate cleanly, waits for the thread handle to signal it is complete and then closes the thread handle
*/
WinUsbDevice::~WinUsbDevice()
{
    this->logger->info("Terminating event loop for %s", this->devicePath);
    this->runEventLoopFlag.clear();
    while (WaitForSingleObject(this->threadHandle, 10) != WAIT_OBJECT_0) {};
    CloseHandle(this->threadHandle);
    this->logger->info("Terminated event loop for %s", this->devicePath);
}

DWORD WINAPI WinUsbDevice::staticRunEventLoop(void * winUsbDeviceInstance) {
    WinUsbDevice* winUsbDevice = (WinUsbDevice*)winUsbDeviceInstance;
    return winUsbDevice->runEventLoop();
}

DWORD WinUsbDevice::runEventLoop(void) {
    this->logger->info("Started event loop for %s", this->devicePath);
    this->runEventLoopFlag.test_and_set();
    while (this->runEventLoopFlag.test_and_set()) {
        // TODO: Implement
    }
    this->logger->info("Completed event loop for %s", this->devicePath);
    return 0;
}

DWORD WinUsbDevice::getThreadId() {
    return this->threadId;
}

/*
Process data read from Razer Atrox
*/
RAZER_ATROX_PACKET_TYPES WinUsbDevice::processInputFromRazerAtrox(RAZER_ATROX_DATA_PACKET &dataPacket, RAZER_ATROX_BUTTON_STATE &buttonState) {
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
bool WinUsbDevice::readInputFromRazerAtrox(DEVICE_DATA &winUsbDeviceData, RAZER_ATROX_DATA_PACKET &dataPacket)
{
    if (winUsbDeviceData.WinusbHandle == INVALID_HANDLE_VALUE) return false;
    return WinUsb_ReadPipe(winUsbDeviceData.WinusbHandle, 0x81, dataPacket.data, 30, &dataPacket.transferred, NULL);
}

/*
Sent the INIT packet to the Razor Atrox
*/
bool WinUsbDevice::initRazorAtrox(DEVICE_DATA &winUsbDeviceData) {
    if (winUsbDeviceData.WinusbHandle == INVALID_HANDLE_VALUE) return false;
    ULONG cbSent = 0;
    return WinUsb_WritePipe(winUsbDeviceData.WinusbHandle, 0x01, RAZER_ATROX_INIT, 5, &cbSent, 0);
}

/*
Initialize the WinUSB device
*/
bool WinUsbDevice::initDevice(DEVICE_DATA &winUsbDeviceData) {
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
bool WinUsbDevice::dispatchInputToVigEmController(PVIGEM_CLIENT vigEmClient, PVIGEM_TARGET vigEmController, RAZER_ATROX_BUTTON_STATE &buttonState) {
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
