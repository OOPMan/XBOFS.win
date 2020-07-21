#pragma once
#include <XBOFS.win/pch.h>
#include <ViGEm/Client.h>
#include <qobject.h>
#include <optional>

namespace XBOFSWin {
    struct STATIC_USB_STRING_DESCRIPTOR {
        UCHAR   bLength;
        UCHAR   bDescriptorType;
        WCHAR   bString[126];
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

    signals:
        void vigEmConnect(const std::wstring &devicePath);
        void vigEmConnected(const std::wstring &devicePath);
        void vigEmTargetAdd(const std::wstring &devicePath);
        void vigEmTargetAdded(const std::wstring &devicePath);        
        void vigEmTargetInfo(const std::wstring &devicePath, quint16 vendorId, quint16 productId, const ulong index);
        void vigEmError(const std::wstring &devicePath);
        void winUsbDeviceOpen(const std::wstring &devicePath);
        void winUsbDeviceInfo(const std::wstring &devicePath, quint16 vendorId, quint16 productId, 
                              const std::wstring &manufacturer, const std::wstring &product, const std::wstring &serialNumber);
        void winUsbDeviceOpened(const std::wstring &devicePath);
        void winUsbDeviceInit(const std::wstring &devicePath);
        void winUsbDeviceInitComplete(const std::wstring &devicePath);
        void winUsbDeviceReadingInput(const std::wstring &devicePath);
        void winUsbDeviceTerminating(const std::wstring &devicePath);
        void winUsbDeviceError(const std::wstring &devicePath);

    protected:        
        const std::shared_ptr<spdlog::logger> logger;
        const std::wstring devicePath;
        std::wstring manufacturer = L"Unknown";
        std::wstring product = L"Unknown";
        std::wstring serialNumber = L"Unknown";

        bool deviceHandlesOpen = false;
        UCHAR XBO_ARCADE_STICK_INIT[5] = { 0x05, 0x20, 0x00, 0x01, 0x00 };
        XBO_ARCADE_STICK_DATA_PACKET dataPacket = {};
        XBO_ARCADE_STICK_BUTTON_STATE buttonState = {};
        PVIGEM_CLIENT vigEmClient = NULL;
        PVIGEM_TARGET vigEmTarget = NULL;
        WINUSB_INTERFACE_HANDLE winUsbHandle;
        HANDLE deviceHandle;        

        bool openDevice();
        bool closeDevice();
        bool initXBOArcadeStick();
        bool readInputFromXBOArcadeStick();
        XBO_ARCADE_STICK_PACKET_TYPES processInputFromXBOArcadeStick();
        bool dispatchInputToVigEmController();
    };
}

