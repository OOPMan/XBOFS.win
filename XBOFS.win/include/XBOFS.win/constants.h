#pragma once
#include <XBOFS.win/pch.h>
#include <ViGEm/Client.h>
#include <qstring.h>

namespace XBOFSWin { 
    namespace settings {
        const QString ORGANIZATION = "OOPMan";
        const QString APPLICATION = "XBOFS.win";
        const QString DEBUG_ENABLED = "debugEnabled";
        const QString BIND_ENABLED = "bindEnabled";
        const QString BINDING_ENABLED = "bindingEnabled";
        const QString ACTIVE_PROFILE = "activeProfile";
        const QString GUIDE_BUTTON_MODE = "guideButtonMode";
        const QString DELETED = "deleted";
        const QString BUTTONS = QString::number(0);
        const QString LEFT_TRIGGER = QString::number(1);
        const QString RIGHT_TRIGGER = QString::number(2);
        const QString THUMB_LX = QString::number(3);
        const QString THUMB_LY = QString::number(4);
        const QString THUMB_RX = QString::number(5);
        const QString THUMB_RY = QString::number(6);
    }

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

    enum class GUIDE_BUTTON_MODE {
        HOLD,
        TOGGLE
    };

    /*
    * Array layout:
    * 1st dimension: Default/Alternate selector
    * 2nd dimension: XBO button selector
    * 3rd dimension: Button OFF/ON selector
    * 4th dimension: XUSB_REPORT structure item selector
    * 
    * E.g. defaultBindings[0][1][1][0] maps to the XUSB_REPORT.wButtons value for the ON state for the Stick Down control for the Default bindings
    * 
    * Columns map to variables in XUSB_REPORT structure:
    * Buttons = wButtons
    * LT = bLeftTrigger
    * RT = bRightTrigger
    * LX = sThumbLX
    * LY = sThumbLY
    * RX = sThumbRX
    * RY = sThumbRY
    */
    const int defaultBindings[2][15][2][7] = {
        // Bindings
        {
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
                {XUSB_GAMEPAD_BACK,            0,      0,      0,      0,      0,      0},     // ON
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
        },
        // Alternate bindings
        {
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
        }
    };

    const int OFF = 0;
    const int ON = 1;

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
