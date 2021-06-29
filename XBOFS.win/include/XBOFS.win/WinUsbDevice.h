#pragma once
#include <XBOFS.win/pch.h>
#include <ViGEm/Client.h>
#include <qobject.h>
#include <qstring.h>
#include <qregularexpression.h>
#include <qsettings.h>
#include <optional>

namespace XBOFSWin {

    enum class XBO_ARCADE_STICK_BUTTONS {
        STICK_UP,
        STICK_DOWN,
        STICK_LEFT,
        STICK_RIGHT,
        X,
        Y,
        A,
        B,
        RB,
        RT,
        LB,
        LT,
        VIEW,
        START,
        GUIDE
    };
    enum class GLOBAL_INPUT_STATE { GUIDE_UP, GUIDE_DOWN };

    /*
    * Columns map to variables in XUSB_REPORT structure:
    * Buttons = wButtons
    * LT = bLeftTrigger
    * RT = bRightTrigger
    * LX = sThumbLX
    * LY = sThumbLY
    * RX = sThumbRX
    * RY = sThumbRY
    */
    const int defaultBindings[15][2][7] = {
            // Buttons                      LT      RT      LX      LY      RX      RY
        {
            // STICK UP
            {0,                             0,      0,      0,      0,      0,      0},     // OFF
            {XUSB_GAMEPAD_DPAD_UP,          0,      0,      0,      0,      0,      0},     // ON
        },
        {
            // STICK DOWN
            {0,                             0,      0,      0,      0,      0,      0},     // OFF
            {XUSB_GAMEPAD_DPAD_DOWN,        0,      0,      0,      0,      0,      0},     // ON
        },
        {
            // STICK LEFT
            {0,                             0,      0,      0,      0,      0,      0},     // OFF
            {XUSB_GAMEPAD_DPAD_LEFT,        0,      0,      0,      0,      0,      0},     // ON
        },
        {
            // STICK RIGHT
            {0,                             0,      0,      0,      0,      0,      0},     // OFF
            {XUSB_GAMEPAD_DPAD_RIGHT,       0,      0,      0,      0,      0,      0},     // STICK_RIGHT
        },
        {
            // X
            {0,                             0,      0,      0,      0,      0,      0},     // OFF
            {XUSB_GAMEPAD_X,                0,      0,      0,      0,      0,      0},     // ON
        },
        {
            // Y
            {0,                             0,      0,      0,      0,      0,      0},     // OFF
            {XUSB_GAMEPAD_Y,                0,      0,      0,      0,      0,      0},     // ON
        },
        {
            // A
            {0,                             0,      0,      0,      0,      0,      0},     // OFF
            {XUSB_GAMEPAD_A,                0,      0,      0,      0,      0,      0},     // ON
        },
        {
            // B
            {0,                             0,      0,      0,      0,      0,      0},     // OFF
            {XUSB_GAMEPAD_B,                0,      0,      0,      0,      0,      0},     // ON
        },
        {
            // RB
            {0,                             0,      0,      0,      0,      0,      0},     // OFF
            {XUSB_GAMEPAD_RIGHT_SHOULDER,   0,      0,      0,      0,      0,      0},     // ON
        },
        {
            // RT
            {0,                             0,      0,      0,      0,      0,      0},     // OFF
            {0,                             0,      0xff,   0,      0,      0,      0},     // ON
        },
        {
            // LB
            {0,                             0,      0,      0,      0,      0,      0},     // OFF
            {XUSB_GAMEPAD_LEFT_SHOULDER,    0,      0,      0,      0,      0,      0},     // ON
        },
        {
            // LT
            {0,                             0,      0,      0,      0,      0,      0},     // OFF
            {0,                             0xff,   0,      0,      0,      0,      0},     // ON
        },
        {
            // VIEW
            {0,                             0,      0,      0,      0,      0,      0},     // OFF
            {XUSB_GAMEPAD_BACK,             0,      0,      0,      0,      0,      0},     // ON
        },
        {
            // START
            {0,                             0,      0,      0,      0,      0,      0},     // ON
            {XUSB_GAMEPAD_START,            0,      0,      0,      0,      0,      0},     // OFF
        },
        {
            // GUIDE
            {0,                             0,      0,      0,      0,      0,      0},     // OFF
            {XUSB_GAMEPAD_GUIDE,            0,      0,      0,      0,      0,      0}      // ON
        }
    };

    /*
    * Columns map to variables in XUSB_REPORT structure:
    * Buttons = wButtons
    * LT = bLeftTrigger
    * RT = bRightTrigger
    * LX = sThumbLX
    * LY = sThumbLY
    * RX = sThumbRX
    * RY = sThumbRY
    */
    const int defaultAlternateBindings[15][2][7] = {
            // Buttons                      LT      RT      LX      LY      RX      RY
        {
            // STICK UP
            {0,                             0,      0,      0,      0,      0,      0},     // OFF
            {XUSB_GAMEPAD_DPAD_UP,          0,      0,      0,      0,      0,      0},     // ON
        },
        {
            // STICK DOWN
            {0,                             0,      0,      0,      0,      0,      0},     // OFF
            {XUSB_GAMEPAD_DPAD_DOWN,        0,      0,      0,      0,      0,      0},     // ON
        },
        {
            // STICK LEFT
            {0,                             0,      0,      0,      0,      0,      0},     // OFF
            {XUSB_GAMEPAD_DPAD_LEFT,        0,      0,      0,      0,      0,      0},     // ON
        },
        {
            // STICK RIGHT
            {0,                             0,      0,      0,      0,      0,      0},     // OFF
            {XUSB_GAMEPAD_DPAD_RIGHT,       0,      0,      0,      0,      0,      0},     // STICK_RIGHT
        },
        {
            // X
            {0,                             0,      0,      0,      0,      0,      0},     // OFF
            {XUSB_GAMEPAD_X,                0,      0,      0,      0,      0,      0},     // ON
        },
        {
            // Y
            {0,                             0,      0,      0,      0,      0,      0},     // OFF
            {XUSB_GAMEPAD_Y,                0,      0,      0,      0,      0,      0},     // ON
        },
        {
            // A
            {0,                             0,      0,      0,      0,      0,      0},     // OFF
            {XUSB_GAMEPAD_A,                0,      0,      0,      0,      0,      0},     // ON
        },
        {
            // B
            {0,                             0,      0,      0,      0,      0,      0},     // OFF
            {XUSB_GAMEPAD_B,                0,      0,      0,      0,      0,      0},     // ON
        },
        {
            // RB
            {0,                             0,      0,      0,      0,      0,      0},     // OFF
            {XUSB_GAMEPAD_RIGHT_SHOULDER,   0,      0,      0,      0,      0,      0},     // ON
        },
        {
            // RT
            {0,                             0,      0,      0,      0,      0,      0},     // OFF
            {0,                             0,      0xff,   0,      0,      0,      0},     // ON
        },
        {
            // LB
            {0,                             0,      0,      0,      0,      0,      0},     // OFF
            {XUSB_GAMEPAD_LEFT_SHOULDER,    0,      0,      0,      0,      0,      0},     // ON
        },
        {
            // LT
            {0,                             0,      0,      0,      0,      0,      0},     // OFF
            {0,                             0xff,   0,      0,      0,      0,      0},     // ON
        },
        {
            // VIEW
            {0,                             0,      0,      0,      0,      0,      0},     // OFF
            {XUSB_GAMEPAD_GUIDE,            0,      0,      0,      0,      0,      0},     // ON
        },
        {
            // START
            {0,                             0,      0,      0,      0,      0,      0},     // ON
            {XUSB_GAMEPAD_START,            0,      0,      0,      0,      0,      0},     // OFF
        },
        {
            // GUIDE
            {0,                             0,      0,      0,      0,      0,      0},     // OFF
            {XUSB_GAMEPAD_GUIDE,            0,      0,      0,      0,      0,      0}      // ON
        }
    };

    struct XBO_ARCADE_STICK_DATA_PACKET
    {
        UCHAR data[30];
        ULONG transferred;
    };

    struct XBO_ARCADE_STICK_BUTTON_STATE
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

    enum class PACKET_TYPES
    {
        UNKNOWN,
        DUMMY,
        HEARTBEAT,
        GUIDE,
        BUTTON_INPUT
    };

    struct STATIC_USB_STRING_DESCRIPTOR {
        UCHAR   bLength;
        UCHAR   bDescriptorType;
        WCHAR   bString[126];
    };

    struct WIN_USB_DEVICE_DETAILS {
        QString vendorId = "";
        QString vendorName = "";
        QString productId = "";
        QString productName = "";
        QString serialNumber = "";
    };

    std::optional<std::wstring> getWinUsbStringDescriptor(const WINUSB_INTERFACE_HANDLE &winUsbHandle, UCHAR index, USHORT languageId);

    class WinUsbDevice : public QObject
    {
        Q_OBJECT

    public:        
        WinUsbDevice(std::wstring devicePath, std::shared_ptr<spdlog::logger> logger, QObject* parent=nullptr);
        ~WinUsbDevice() {};        

    public slots:
        void run();
        void refreshSettings();

    signals:
        void vigEmConnect(const std::wstring &devicePath);
        void vigEmConnected(const std::wstring &devicePath);
        void vigEmTargetAdd(const std::wstring &devicePath);
        void vigEmTargetAdded(const std::wstring &devicePath);        
        void vigEmTargetInfo(const std::wstring &devicePath, quint16 vendorId, quint16 productId, const ulong index);
        void vigEmError(const std::wstring &devicePath);
        void winUsbDeviceOpen(const std::wstring &devicePath);
        void winUsbDeviceInfo(const std::wstring &devicePath, const QString &vendorId, const QString &vendorName,
                              const QString &productId, const QString &productName, const QString &serialNumber);
        void winUsbDeviceOpened(const std::wstring &devicePath);
        void winUsbDeviceInit(const std::wstring &devicePath);
        void winUsbDeviceInitComplete(const std::wstring &devicePath);
        void winUsbDeviceReadingInput(const std::wstring &devicePath);
        void winUsbDeviceTerminating(const std::wstring &devicePath);
        void winUsbDeviceError(const std::wstring &devicePath);

        void debuggingInfoButtonState(const XBO_ARCADE_STICK_BUTTON_STATE &buttonState);
        void debuggingInfoControllerState(const XUSB_REPORT &controllerState);
        void debuggingInfoPerformanceData(quint16 lastInnerLoopTime, quint16 worstInnerLoopTime, quint16 averageInnerLoopTime, quint16 bestInnerLoopTime);

    protected:        
        const std::shared_ptr<spdlog::logger> logger;
        const std::wstring devicePath;
        const QSettings settings;
        QString vendorId = "";
        QString vendorName = "";
        QString productId = "";
        QString productName = "";
        QString serialNumber = "";
        GLOBAL_INPUT_STATE state = GLOBAL_INPUT_STATE::GUIDE_UP;
        bool bindingEnabled = false;
        bool debuggingEnabled = false;

        bool buttons[15] = {false, false, false, false, false, false, false, false, false, false, false, false, false, false, false};

        bool deviceHandlesOpen = false;
        UCHAR XBO_ARCADE_STICK_INIT[5] = { 0x05, 0x20, 0x00, 0x01, 0x00 };
        XBO_ARCADE_STICK_DATA_PACKET dataPacket = {};
        XBO_ARCADE_STICK_BUTTON_STATE buttonState = {};
        XBO_ARCADE_STICK_BUTTON_STATE previousButtonState = {};
        PVIGEM_CLIENT vigEmClient = NULL;
        PVIGEM_TARGET vigEmTarget = NULL;
        WINUSB_INTERFACE_HANDLE winUsbHandle;
        HANDLE deviceHandle;        

        bool openDevice();
        bool closeDevice();
        bool initXBOArcadeStick();
        bool readInputFromXBOArcadeStick();
        PACKET_TYPES processInputFromXBOArcadeStick();
        XUSB_REPORT prepareInputForVigEmController();
        bool dispatchInputToVigEmController();
    };
}

