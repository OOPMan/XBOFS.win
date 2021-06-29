#pragma once
#include <XBOFS.win/pch.h>
#include <ViGEm/Client.h>

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

}
