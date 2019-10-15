#include <qthread.h>
#include <qabstracteventdispatcher.h>
#include <qeventloop.h>

#include "XBOFS.win\WinUsbDevice.h"

using namespace XBOFSWin;
/*
Constructs the WinUsbDevice instance and starts its event loop in a separate thread
*/
WinUsbDevice::WinUsbDevice(std::wstring devicePath, std::shared_ptr<spdlog::logger> logger, QObject* parent)
: QObject(parent), devicePath(devicePath), logger(logger)
{
    
}

void WinUsbDevice::run() {    
    logger->info("Entered run()");
    bool loop = true;
    int failedReads = 0;
    int failedWrites = 0;    
    // Allocate objects for VigEm        
    vigEmClient = vigem_alloc();    
    vigEmTarget = vigem_target_x360_alloc();
    // Connect to VigEm
    logger->info("Connecting VigEmClient");    
    emit vigEmConnect(devicePath);
    if (!VIGEM_SUCCESS(vigem_connect(vigEmClient))) {
        emit vigEmError(devicePath);
        logger->error("Unable to connect VigEmClient");
        loop = false;
    }   
    emit vigEmConnected(devicePath);
    // Add VigEm Target
    logger->info("Adding VigEmTarget");
    emit vigEmTargetAdd(devicePath);
    if (!VIGEM_SUCCESS(vigem_target_add(vigEmClient, vigEmTarget))) {
        emit vigEmError(devicePath);
        logger->error("Unable to add VigEmTarget");
        loop = false;
    }
    emit vigEmTargetAdded(devicePath);
    // Loop reading input, processing it and dispatching it
    logger->info("Starting Read-Process-Dispatch loop");
    while (loop && !QThread::currentThread()->isInterruptionRequested()) {                
        // Open WinUsbDevice
        emit winUsbDeviceOpen(devicePath);
        if (!openDevice()) {
            emit winUsbDeviceError(devicePath);            
            logger->error("Unable to open WinUSB device");
            continue;
        }        
        emit winUsbDeviceOpened(devicePath);
        // Init WinUsbDevice
        emit winUsbDeviceInit(devicePath);       
        if (!initXBOArcadeStick()) {
            emit winUsbDeviceError(devicePath);            
            logger->error("Unable to init XBO Arcade Stick"); // TODO: Provide more details on stick vendor&product
            continue;
        }
        emit winUsbDeviceInitComplete(devicePath);
        // Read input
        emit winUsbDeviceReadingInput(devicePath);        
        logger->info("Reading input from XBO Arcade Stick"); // TODO: Provide more details on stick vendor&product
        int currentFailedReads = 0;
        while (loop && currentFailedReads < 5 && !QThread::currentThread()->isInterruptionRequested()) {            
            if (!readInputFromXBOArcadeStick()) {                
                logger->warn("Failed to read input from XBO Arcade Stick"); // TODO: Provide more details on stick vendor&product
                currentFailedReads += 1;
                continue;
            }
            processInputFromXBOArcadeStick();
            if (!dispatchInputToVigEmController()) failedWrites += 1;
        }
        if (currentFailedReads >= 5) {
            emit winUsbDeviceError(devicePath);            
            logger->warn("Failed to read input from XBO Arcade Stick 5 or more times for {}");
        }
        failedReads += currentFailedReads;
        currentFailedReads = 0;
        QThread::currentThread()->eventDispatcher()->processEvents(QEventLoop::AllEvents);
    }
    emit winUsbDeviceTerminating(devicePath);    
    logger->info("Completed Read-Process-Dispatch loop");
    logger->info("There were {} failed reads", failedReads);
    logger->info("There were {} failed writes", failedWrites);
    logger->info("Closing WinUSB device");
    closeDevice();
    logger->info("Removing VigEmTarget");
    vigem_target_remove(vigEmClient, vigEmTarget);
    logger->info("Disconnecting VigEmClient");
    vigem_disconnect(vigEmClient);    
    vigem_target_free(vigEmTarget);    
    vigem_free(vigEmClient);
    logger->info("Completed run()");    
}

/*
Attempt to open and initialize the WinUsb device
*/
bool WinUsbDevice::openDevice() {
    HRESULT hr = S_OK;
    BOOL    bResult;
    deviceHandlesOpen = false;
    logger->info("Opening WinUSB device");
    // Attempt to open device handle
    deviceHandle = CreateFile(devicePath.c_str(),
        GENERIC_WRITE | GENERIC_READ,
        FILE_SHARE_WRITE | FILE_SHARE_READ,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED,
        NULL);
    if (INVALID_HANDLE_VALUE == deviceHandle) {
        hr = HRESULT_FROM_WIN32(GetLastError());
        logger->error("Failed to open device handle due to {}", hr);
        return false;
    }
    // Initialize WinUsb handle
    bResult = WinUsb_Initialize(deviceHandle, &winUsbHandle);
    if (FALSE == bResult) {
        hr = HRESULT_FROM_WIN32(GetLastError());
        CloseHandle(deviceHandle);
        logger->error("Failed to initiallize WinUSB handle due to {}", hr);
        return false;
    }
    deviceHandlesOpen = true;
    // Make GetDescriptor call to device in order to ensure communications with it work
    BOOL winUsbGetDescriptorResult;
    USB_DEVICE_DESCRIPTOR winUsbDeviceDescriptor;
    ULONG bytesReceived;
    winUsbGetDescriptorResult = WinUsb_GetDescriptor(
        winUsbHandle, USB_DEVICE_DESCRIPTOR_TYPE, 0, 0, (PBYTE)&winUsbDeviceDescriptor, sizeof(winUsbDeviceDescriptor), &bytesReceived
    );
    if (winUsbGetDescriptorResult == FALSE || bytesReceived != sizeof(winUsbDeviceDescriptor)) {
        logger->error("Failed to read USB descriptor");
        closeDevice();
        return false;
    } 
    // TODO: Emit USB descriptor result
    logger->info("Opened WinUSB device");
    return true;
}

/*
Attempt to close the WinUsb device
*/
bool WinUsbDevice::closeDevice() {
    if (!deviceHandlesOpen) return false;
    WinUsb_Free(winUsbHandle);
    CloseHandle(deviceHandle);
    deviceHandlesOpen = false;    
    return true;    
}

/*
Process data read from XBO Arcade Stick
*/
XBO_ARCADE_STICK_PACKET_TYPES WinUsbDevice::processInputFromXBOArcadeStick() {
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
bool WinUsbDevice::readInputFromXBOArcadeStick()
{
    if (winUsbHandle == INVALID_HANDLE_VALUE) return false;
    return WinUsb_ReadPipe(winUsbHandle, 0x81, dataPacket.data, 30, &dataPacket.transferred, NULL);
}

/*
Sent the INIT packet to the Razor Atrox
*/
bool WinUsbDevice::initXBOArcadeStick() {
    logger->info("Init XBO Arcade Stick");
    if (winUsbHandle == INVALID_HANDLE_VALUE) return false;
    ULONG cbSent = 0;
    return WinUsb_WritePipe(winUsbHandle, 0x01, (PUCHAR)XBO_ARCADE_STICK_INIT, 5, &cbSent, 0);
}

/*
Dispatch data to the VigEm XB360 controller
*/
bool WinUsbDevice::dispatchInputToVigEmController() {
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
    const auto controllerUpdateResult = vigem_target_x360_update(vigEmClient, vigEmTarget, controllerData);
    return VIGEM_SUCCESS(controllerUpdateResult);
}
