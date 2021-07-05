#pragma once
#include <XBOFS.win/pch.h>
#include <XBOFS.win/constants.h>
#include <ViGEm/Client.h>
#include <qobject.h>
#include <qstring.h>
#include <qregularexpression.h>
#include <qsettings.h>
#include <optional>
#include <chrono>

namespace XBOFSWin {

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

        void debugInfoLoopTime(const std::chrono::microseconds &loopTime);
        void debugInfoButtons(
            const bool &stickUp,
            const bool &stickDown,
            const bool &stickLeft,
            const bool &stickRight,
            const bool &x,
            const bool &y,
            const bool &a,
            const bool &b,
            const bool &rb,
            const bool &rt,
            const bool &lb,
            const bool &lt,
            const bool &view,
            const bool &start,
            const bool &guide
        );
        void debugInfoXUSB_REPORT(
            const USHORT wButtons,
            const BYTE   bLeftTrigger,
            const BYTE   bRightTrigger,
            const SHORT  sThumbLX,
            const SHORT  sThumbLY,
            const SHORT  sThumbRX,
            const SHORT  sThumbRY
        );

    protected:   
        enum class READ_INPUT_INNER_LOOP_RESULT {
            SUCCESS,
            READ_FAILED,
            WRITE_FAILED
        };

        const std::shared_ptr<spdlog::logger> logger;
        const std::wstring devicePath;
        QSettings settings = QSettings(settings::ORGANIZATION, settings::APPLICATION);
        QString vendorId = "";
        QString vendorName = "";
        QString productId = "";
        QString productName = "";
        QString serialNumber = "";
        bool bindingEnabled = false;
        bool debugEnabled = false;
        QString activeProfile;

        bool bindingSelector = 0;
        int bindings[2][15][2][7] = {};
        bool buttons[15] = {false, false, false, false, false, false, false, false, false, false, false, false, false, false, false};
        GUIDE_BUTTON_MODE guideButtonMode;

        bool deviceHandlesOpen = false;
        UCHAR XBO_ARCADE_STICK_INIT[5] = { 0x05, 0x20, 0x00, 0x01, 0x00 };
        XBO_ARCADE_STICK_DATA_PACKET dataPacket = {};
        PVIGEM_CLIENT vigEmClient = NULL;
        PVIGEM_TARGET vigEmTarget = NULL;
        WINUSB_INTERFACE_HANDLE winUsbHandle;
        HANDLE deviceHandle;      

        READ_INPUT_INNER_LOOP_RESULT debugDisabledReadInputInnerLoop();
        READ_INPUT_INNER_LOOP_RESULT debugEnabledReadInputInnerLoop();
        READ_INPUT_INNER_LOOP_RESULT(WinUsbDevice::* readInputInnerLoop)() = &WinUsbDevice::debugDisabledReadInputInnerLoop;

        bool openDevice();
        bool closeDevice();
        bool initXBOArcadeStick();
        bool readInputFromXBOArcadeStick();
        PACKET_TYPES processInputFromXBOArcadeStick();
        XUSB_REPORT prepareInputForVigEmController();
        bool dispatchInputToVigEmController();
        bool debugDispatchInputToVigEmController();
    };
}

