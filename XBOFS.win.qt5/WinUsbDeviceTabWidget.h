#pragma once

#include <XBOFS.win/WinUsbDevice.h>
#include <QWidget>
#include <qsettings.h>
#include <qregularexpression.h>
#include "ui_WinUsbDeviceWidget.h"
#include "ConfigureBindingsDialog.h"
#include "ui_DebuggingWidget.h"

class WinUsbDeviceTabWidget : public QWidget
{
    Q_OBJECT

public:
    WinUsbDeviceTabWidget(QWidget *parent, QString devicePath, const XBOFSWin::WinUsbDevice *winUsbDevice, QSettings *settings, std::shared_ptr<spdlog::logger> logger);
    ~WinUsbDeviceTabWidget();

public slots:
    void handleVigEmConnect(const std::wstring &devicePath);
    void handleVigEmConnected(const std::wstring &devicePath);
    void handleVigEmTargetAdd(const std::wstring &devicePath);
    void handleVigEmTargetAdded(const std::wstring &devicePath);
    void handleVigEmTargetInfo(const std::wstring &devicePath, quint16 vendorId, quint16 productId, const ulong index);
    void handleVigEmError(const std::wstring &devicePath);
    void handleWinUsbDeviceOpen(const std::wstring &devicePath);
    void handleWinUsbDeviceInfo(const std::wstring &devicePath, const QString &vendorId, const QString &vendorName,
                                const QString &productId, const QString &productName, const QString &serialNumber);   
    void handleWinUsbDeviceOpened(const std::wstring &devicePath);
    void handleWinUsbDeviceInit(const std::wstring &devicePath);
    void handleWinUsbDeviceInitComplete(const std::wstring &devicePath);
    void handleWinUsbDeviceReadingInput(const std::wstring &devicePath);
    void handleWinUsbDeviceTerminating(const std::wstring &devicePath);
    void handleWinUsbDeviceError(const std::wstring &devicePath);

    void handleBindingEnabledCheckBoxStateChanged(int state);
    void handleConfigureBindingsPushButtonClicked(bool checked = false);
    void handleConfigureGuideDownBindingsPushButtonClicked(bool checked = false);

protected:
    const std::shared_ptr<spdlog::logger> logger;
    QString settingsKey;
    QSettings* settings;
    QString vendorId;
    QString vendorName;
    QString productId;
    QString productName;
    QString serialNumber;
    Ui::WinUsbDeviceWidget ui;
    const XBOFSWin::WinUsbDevice* winUsbDevice;
    ConfigureBindingsDialog* configureBindingsDialog;
    ConfigureBindingsDialog* configureGuideDownBindingsDialog;
};
