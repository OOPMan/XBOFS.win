#pragma once

#include <XBOFS.win/WinUsbDevice.h>
#include <QWidget>
#include "ui_WinUsbDeviceWidget.h"

class WinUsbDeviceTabWidget : public QWidget
{
    Q_OBJECT

public:
    WinUsbDeviceTabWidget(QWidget *parent, QString devicePath, const XBOFSWin::WinUsbDevice *winUsbDevice, std::shared_ptr<spdlog::logger> logger);
    ~WinUsbDeviceTabWidget();

public slots:
    void handleVigEmConnect(const std::wstring &devicePath);
    void handleVigEmConnected(const std::wstring &devicePath);
    void handleVigEmTargetAdd(const std::wstring &devicePath);
    void handleVigEmTargetAdded(const std::wstring &devicePath);
    void handleVigEmTargetInfo(const std::wstring &devicePath, quint16 vendorId, quint16 productId, const ulong index);
    void handleVigEmError(const std::wstring &devicePath);
    void handleWinUsbDeviceOpen(const std::wstring &devicePath);
    void handleWinUsbDeviceInfo(const std::wstring &devicePath, quint16 vendorId, quint16 productId,
                                const std::wstring &manufacturer, const std::wstring &product, const std::wstring &serialNumber);
    void handleWinUsbDeviceOpened(const std::wstring &devicePath);
    void handleWinUsbDeviceInit(const std::wstring &devicePath);
    void handleWinUsbDeviceInitComplete(const std::wstring &devicePath);
    void handleWinUsbDeviceReadingInput(const std::wstring &devicePath);
    void handleWinUsbDeviceTerminating(const std::wstring &devicePath);
    void handleWinUsbDeviceError(const std::wstring &devicePath);

    void handleBindingEnabledCheckBoxStateChanged(int state);

protected:
    const std::shared_ptr<spdlog::logger> logger;
    Ui::WinUsbDeviceWidget ui;
    const XBOFSWin::WinUsbDevice* winUsbDevice;
};
