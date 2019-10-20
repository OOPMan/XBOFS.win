#pragma once

#include <optional>
#include <spdlog/spdlog.h>
#include <XBOFS.win/WinUsbDeviceManager.h>
#include <XBOFS.win/WinUsbDevice.h>

#include <QtWidgets/QMainWindow>
#include "ui_XBOFSWinQT5GUI.h"
#include "ui_WinUsbDeviceWidget.h"

namespace std {
    template<> struct hash<QString> {
        std::size_t operator()(const QString& s) const {
            return qHash(s);
        }
    };
}

class XBOFSWinQT5GUI : public QMainWindow
{
    Q_OBJECT

public:
    XBOFSWinQT5GUI(QWidget *parent = Q_NULLPTR);
    //~XBOFSWinQT5GUI();

public slots:
    void handleWinUsbDeviceAdded(const std::wstring &devicePath, const XBOFSWin::WinUsbDevice *winUsbDevice);
    void handleWinUsbDeviceRemoved(const std::wstring &devicePath);
    void handleWinUsbDeviceManagerScanning();
    void handleTerminateWinUsbDeviceManager();
    void handleVigEmConnect(const std::wstring &devicePath);
    void handleVigEmConnected(const std::wstring &devicePath);
    void handleVigEmTargetAdd(const std::wstring &devicePath);
    void handleVigEmTargetAdded(const std::wstring &devicePath);
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

protected:
    Ui::XBOFSWinQT5GUIClass ui;        
    std::shared_ptr<spdlog::logger> logger;
    QThread *winUsbDeviceManagerThread;
    XBOFSWin::WinUsbDeviceManager *winUsbDeviceManager;

    std::vector<std::tuple<std::wstring, QWidget*, Ui::WinUsbDeviceWidget*>> tabs;    

    std::optional<std::pair<int, std::vector<std::tuple<std::wstring, QWidget*, Ui::WinUsbDeviceWidget*>>::iterator>> getIteratorForDevicePath(const std::wstring &devicePath);    
};
