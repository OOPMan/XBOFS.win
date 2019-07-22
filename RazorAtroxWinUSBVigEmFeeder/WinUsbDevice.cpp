#include "WinUsbDevice.h"

/*
Constructs the WinUsbDevice instance and starts its event loop in a separate thread
*/
WinUsbDevice::WinUsbDevice(tstring devicePath, DWORD parentThreadId, DWORD uiManagerThreadId)
{
    this->devicePath = devicePath;
    this->parentThreadId = parentThreadId;
    this->uiManagerThreadId = uiManagerThreadId;
    this->logger->info("Starting event loop for %v", devicePath);
    this->threadHandle = CreateThread(NULL, 0, staticRunEventLoop, (void*)this, 0, &this->threadId);
}

/*
Signals the event loop to terminate cleanly, waits for the thread handle to signal it is complete and then closes the thread handle
*/
WinUsbDevice::~WinUsbDevice()
{
    this->logger->info("Terminating event loop for %v", this->devicePath);
    this->runEventLoopFlag.clear();
    while (WaitForSingleObject(this->threadHandle, 10) != WAIT_OBJECT_0) {};
    CloseHandle(this->threadHandle);
    this->logger->info("Terminated event loop for %v", this->devicePath);
}

DWORD WinUsbDevice::getThreadId() {
    return this->threadId;
}

DWORD WINAPI WinUsbDevice::staticRunEventLoop(void * winUsbDeviceInstance) {
    WinUsbDevice* winUsbDevice = (WinUsbDevice*)winUsbDeviceInstance;
    return winUsbDevice->runEventLoop();
}

DWORD WinUsbDevice::runEventLoop(void) {    
    int failedReads = 0;
    int failedWrites = 0;
    MSG threadMessage;
    PeekMessage(&threadMessage, NULL, WM_USER, WM_USER, PM_NOREMOVE);
    this->logger->info("Started event loop for %v", this->devicePath);
    this->runEventLoopFlag.test_and_set();
    this->logger->info("Allocating VigEmClient for %v", this->devicePath);
    this->vigEmClient = vigem_alloc();
    this->logger->info("Allocating VigEmTarget for %v", this->devicePath);
    this->vigEmTarget = vigem_target_x360_alloc();
    // TODO: turn this block into a method?
    this->logger->info("Connecting VigEmClient for %v", this->devicePath);
    if (!VIGEM_SUCCESS(vigem_connect(this->vigEmClient))) {
        this->logger->error("Unable to connect VigEmClient for %v", this->devicePath);
        this->runEventLoopFlag.clear();      
    }
    // TODO: turn this block into a method?
    this->logger->info("Adding VigEmTarget for %v", this->devicePath);
    if (!VIGEM_SUCCESS(vigem_target_add(this->vigEmClient, this->vigEmTarget))) {
        this->logger->error("Unable to add VigEmTarget for %v", this->devicePath);
        this->runEventLoopFlag.clear();
    }
    // Loop reading input, processing it and dispatching it
    while (this->runEventLoopFlag.test_and_set()) {                        
        if (!this->openDevice()) {
            this->logger->error("Unable to open WinUSB device for %v", this->devicePath);
            continue;
        }        
        if (!this->initRazorAtrox()) {
            this->logger->error("Unable to init Razer Atrox for %v", this->devicePath);
            continue;
        }
        this->logger->info("Reading input from Razer Atrox for %v", this->devicePath);
        int currentFailedReads = 0;
        while (this->runEventLoopFlag.test_and_set() && currentFailedReads < 5) {
            if (!this->readInputFromRazerAtrox()) {
                this->logger->warn("Failed to read input from Razer Atrox for %v", this->devicePath);
                currentFailedReads += 1;
                continue;
            }
            this->processInputFromRazerAtrox();
            if (!this->dispatchInputToVigEmController()) failedWrites += 1;
        }
        if (currentFailedReads >= 5) this->logger->warn("Failed to read input from Razer Atrox 5 or more times for %v", this->devicePath);
        failedReads += currentFailedReads;
        currentFailedReads = 0;
    }
    this->logger->info("Completed Read-Process-Dispatch loop %v", this->devicePath);
    this->logger->info("There were %v failed reads for %v", failedReads, this->devicePath);
    this->logger->info("There were %v failed writes for %v", failedWrites, this->devicePath);
    this->logger->info("Closing WinUSB device for %v", this->devicePath);
    this->closeDevice();
    this->logger->info("Removing VigEmTarget for %v", this->devicePath);
    vigem_target_remove(this->vigEmClient, this->vigEmTarget);
    this->logger->info("Disconnecting VigEmClient for %v", this->devicePath);
    vigem_disconnect(vigEmClient);
    this->logger->info("Free VigEmTarget for %v", this->vigEmTarget);
    vigem_target_free(this->vigEmTarget);
    this->logger->info("Free VigEmClient for %v", this->devicePath);
    vigem_free(this->vigEmClient);
    this->logger->info("Completed event loop for %v", this->devicePath);
    return 0;
}

/*
Attempt to open and initialize the WinUsb device
*/
bool WinUsbDevice::openDevice() {
    HRESULT hr = S_OK;
    BOOL    bResult;
    this->deviceHandlesOpen = false;
    this->logger->info("Opening WinUSB device for %v", this->devicePath);
    // Attempt to open device handle
    this->deviceHandle = CreateFile(this->devicePath.c_str(),
        GENERIC_WRITE | GENERIC_READ,
        FILE_SHARE_WRITE | FILE_SHARE_READ,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED,
        NULL);
    if (INVALID_HANDLE_VALUE == this->deviceHandle) {
        hr = HRESULT_FROM_WIN32(GetLastError());
        this->logger->error("Failed to open device handle for %v due to %v", this->devicePath, hr);
        return false;
    }
    // Initialize WinUsb handle
    bResult = WinUsb_Initialize(this->deviceHandle, &this->winUsbHandle);
    if (FALSE == bResult) {
        hr = HRESULT_FROM_WIN32(GetLastError());
        CloseHandle(this->deviceHandle);
        this->logger->error("Failed to initiallize WinUSB handle for %v due to %v", this->devicePath, hr);
        return false;
    }
    this->deviceHandlesOpen = true;
    // Make GetDescriptor call to device in order to ensure communications with it work
    BOOL winUsbGetDescriptorResult;
    USB_DEVICE_DESCRIPTOR winUsbDeviceDescriptor;
    ULONG bytesReceived;
    winUsbGetDescriptorResult = WinUsb_GetDescriptor(
        this->winUsbHandle, USB_DEVICE_DESCRIPTOR_TYPE, 0, 0, (PBYTE)&winUsbDeviceDescriptor, sizeof(winUsbDeviceDescriptor), &bytesReceived
    );
    if (winUsbGetDescriptorResult == FALSE || bytesReceived != sizeof(winUsbDeviceDescriptor)) {
        this->logger->error("Failed to read USB descriptor for %v", this->devicePath);
        this->closeDevice();
        return false;
    }
    this->logger->info("Opened WinUSB device for %v", this->devicePath);
    return true;
}

/*
Attempt to close the WinUsb device
*/
bool WinUsbDevice::closeDevice() {
    if (!this->deviceHandlesOpen) return false;
    WinUsb_Free(this->winUsbHandle);
    CloseHandle(this->deviceHandle);
    this->deviceHandlesOpen = false;    
    return true;    
}

/*
Process data read from Razer Atrox
*/
RAZER_ATROX_PACKET_TYPES WinUsbDevice::processInputFromRazerAtrox() {
    if (this->dataPacket.transferred == 0) return UNKNOWN;
    switch (this->dataPacket.data[0]) {
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
bool WinUsbDevice::readInputFromRazerAtrox()
{
    if (this->winUsbHandle == INVALID_HANDLE_VALUE) return false;
    return WinUsb_ReadPipe(this->winUsbHandle, 0x81, this->dataPacket.data, 30, &this->dataPacket.transferred, NULL);
}

/*
Sent the INIT packet to the Razor Atrox
*/
bool WinUsbDevice::initRazorAtrox() {
    this->logger->info("Init Razer Atrox for %v", this->devicePath);
    if (this->winUsbHandle == INVALID_HANDLE_VALUE) return false;
    ULONG cbSent = 0;
    return WinUsb_WritePipe(this->winUsbHandle, 0x01, this->RAZER_ATROX_INIT, 5, &cbSent, 0);
}

/*
Dispatch data to the VigEm XB360 controller
*/
bool WinUsbDevice::dispatchInputToVigEmController() {
    XUSB_REPORT controllerData{};
    if (this->buttonState.buttonGuide)    controllerData.wButtons |= XUSB_GAMEPAD_GUIDE;
    if (this->buttonState.buttonMenu)     controllerData.wButtons |= XUSB_GAMEPAD_START;
    if (this->buttonState.buttonView)     controllerData.wButtons |= XUSB_GAMEPAD_BACK;
    if (this->buttonState.buttonA)        controllerData.wButtons |= XUSB_GAMEPAD_A;
    if (this->buttonState.buttonB)        controllerData.wButtons |= XUSB_GAMEPAD_B;
    if (this->buttonState.buttonX)        controllerData.wButtons |= XUSB_GAMEPAD_X;
    if (this->buttonState.buttonY)        controllerData.wButtons |= XUSB_GAMEPAD_Y;
    if (this->buttonState.leftButton)     controllerData.wButtons |= XUSB_GAMEPAD_LEFT_SHOULDER;
    if (this->buttonState.rightButton)    controllerData.wButtons |= XUSB_GAMEPAD_RIGHT_SHOULDER;
    if (this->buttonState.stickUp)        controllerData.wButtons |= XUSB_GAMEPAD_DPAD_UP;
    if (this->buttonState.stickDown)      controllerData.wButtons |= XUSB_GAMEPAD_DPAD_DOWN;
    if (this->buttonState.stickLeft)      controllerData.wButtons |= XUSB_GAMEPAD_DPAD_LEFT;
    if (this->buttonState.stickRight)     controllerData.wButtons |= XUSB_GAMEPAD_DPAD_RIGHT;
    if (this->buttonState.leftTrigger)    controllerData.bLeftTrigger = 0xff;
    if (this->buttonState.rightTrigger)   controllerData.bRightTrigger = 0xff;
    const auto controllerUpdateResult = vigem_target_x360_update(this->vigEmClient, this->vigEmTarget, controllerData);
    return VIGEM_SUCCESS(controllerUpdateResult);
}
