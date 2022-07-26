#pragma once
#include "pch.h"
#include "ViGEm/Client.h"
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
        const QString SOCD_CLEANING_ENABLED = "socdCleaningEnabled";
        const QString SOCD_CLEAN_UP_DOWN_TO = "socdCleanUpDownTo";
        const QString SOCD_CLEAN_LEFT_RIGHT_TO = "socdCleanLeftRightTo";
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
        TOGGLE,
        NORMAL
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

    /*
    * SOCD constants
    */
    enum class SOCD_CLEANING_UP_DOWN_OPTIONS {
        NEUTRAL,
        UP,
        DOWN
    };

    enum class SOCD_CLEANING_LEFT_RIGHT_OPTIONS {
        NEUTRAL,
        LEFT,
        RIGHT
    };

    const int SOCD_UP_DOWN_MASK = XUSB_GAMEPAD_DPAD_UP | XUSB_GAMEPAD_DPAD_DOWN;
    const int SOCD_LEFT_RIGHT_MASK = XUSB_GAMEPAD_DPAD_LEFT | XUSB_GAMEPAD_DPAD_RIGHT;
    const int SOCD_ALL_BUTTONS_MASK =
        XUSB_GAMEPAD_DPAD_UP | XUSB_GAMEPAD_DPAD_DOWN | XUSB_GAMEPAD_DPAD_LEFT | XUSB_GAMEPAD_DPAD_RIGHT |
        XUSB_GAMEPAD_START | XUSB_GAMEPAD_BACK | XUSB_GAMEPAD_LEFT_THUMB | XUSB_GAMEPAD_RIGHT_THUMB |
        XUSB_GAMEPAD_LEFT_SHOULDER | XUSB_GAMEPAD_RIGHT_SHOULDER | XUSB_GAMEPAD_GUIDE |
        XUSB_GAMEPAD_A | XUSB_GAMEPAD_B | XUSB_GAMEPAD_X | XUSB_GAMEPAD_Y;
    const int SOCD_NEGATE_UP_DOWN = SOCD_ALL_BUTTONS_MASK ^ (XUSB_GAMEPAD_DPAD_UP | XUSB_GAMEPAD_DPAD_DOWN);
    const int SOCD_NEGATE_UP = SOCD_ALL_BUTTONS_MASK ^ XUSB_GAMEPAD_DPAD_UP;
    const int SOCD_NEGATE_DOWN = SOCD_ALL_BUTTONS_MASK ^ XUSB_GAMEPAD_DPAD_DOWN;
    const int SOCD_NEGATE_LEFT_RIGHT = SOCD_ALL_BUTTONS_MASK ^ (XUSB_GAMEPAD_DPAD_LEFT | XUSB_GAMEPAD_DPAD_RIGHT);
    const int SOCD_NEGATE_LEFT = SOCD_ALL_BUTTONS_MASK ^ XUSB_GAMEPAD_DPAD_LEFT;
    const int SOCD_NEGATE_RIGHT = SOCD_ALL_BUTTONS_MASK ^ XUSB_GAMEPAD_DPAD_RIGHT;

    const std::map<SOCD_CLEANING_UP_DOWN_OPTIONS, int> socdCleaningUpDownOptionsMapping {
        {SOCD_CLEANING_UP_DOWN_OPTIONS::NEUTRAL, SOCD_NEGATE_UP_DOWN},
        {SOCD_CLEANING_UP_DOWN_OPTIONS::UP, SOCD_NEGATE_DOWN},
        {SOCD_CLEANING_UP_DOWN_OPTIONS::DOWN, SOCD_NEGATE_UP}
    };

    const std::map<SOCD_CLEANING_LEFT_RIGHT_OPTIONS, int> socdCleaningLeftRightOptionsMapping{
        {SOCD_CLEANING_LEFT_RIGHT_OPTIONS::NEUTRAL, SOCD_NEGATE_LEFT_RIGHT},
        {SOCD_CLEANING_LEFT_RIGHT_OPTIONS::LEFT, SOCD_NEGATE_RIGHT},
        {SOCD_CLEANING_LEFT_RIGHT_OPTIONS::RIGHT, SOCD_NEGATE_LEFT}
    };

    struct SOCD_CLEANING_CONFIGURATION {
        std::map<int, int> upDownMasks {
            {0, SOCD_ALL_BUTTONS_MASK},
            {XUSB_GAMEPAD_DPAD_UP, SOCD_ALL_BUTTONS_MASK},
            {XUSB_GAMEPAD_DPAD_DOWN, SOCD_ALL_BUTTONS_MASK}
        };
        std::map<int, int> leftRightMasks {
            {0, SOCD_ALL_BUTTONS_MASK},
            {XUSB_GAMEPAD_DPAD_LEFT, SOCD_ALL_BUTTONS_MASK},
            {XUSB_GAMEPAD_DPAD_RIGHT, SOCD_ALL_BUTTONS_MASK}
        };
    };
}
