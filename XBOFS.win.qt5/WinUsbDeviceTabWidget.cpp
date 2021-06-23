#include "WinUsbDeviceTabWidget.h"

WinUsbDeviceTabWidget::WinUsbDeviceTabWidget(QWidget *parent, QString devicePath, const XBOFSWin::WinUsbDevice *winUsbDevice, std::shared_ptr<spdlog::logger> logger)
    : QWidget(parent), winUsbDevice(winUsbDevice), logger(logger)
{
    configureBindingsDialog = new ConfigureBindingsDialog(this);
    configureGuideDownBindingsDialog = new ConfigureBindingsDialog(this);
    setObjectName(devicePath);
    ui.setupUi(this);
    connect(winUsbDevice, &XBOFSWin::WinUsbDevice::vigEmConnect, this, &WinUsbDeviceTabWidget::handleVigEmConnect);
    connect(winUsbDevice, &XBOFSWin::WinUsbDevice::vigEmConnected, this, &WinUsbDeviceTabWidget::handleVigEmConnected);
    connect(winUsbDevice, &XBOFSWin::WinUsbDevice::vigEmTargetAdd, this, &WinUsbDeviceTabWidget::handleVigEmTargetAdd);
    connect(winUsbDevice, &XBOFSWin::WinUsbDevice::vigEmTargetAdded, this, &WinUsbDeviceTabWidget::handleVigEmTargetAdded);
    connect(winUsbDevice, &XBOFSWin::WinUsbDevice::vigEmTargetInfo, this, &WinUsbDeviceTabWidget::handleVigEmTargetInfo);
    connect(winUsbDevice, &XBOFSWin::WinUsbDevice::vigEmError, this, &WinUsbDeviceTabWidget::handleVigEmError);
    connect(winUsbDevice, &XBOFSWin::WinUsbDevice::winUsbDeviceOpen, this, &WinUsbDeviceTabWidget::handleWinUsbDeviceOpen);
    connect(winUsbDevice, &XBOFSWin::WinUsbDevice::winUsbDeviceOpened, this, &WinUsbDeviceTabWidget::handleWinUsbDeviceOpened);
    connect(winUsbDevice, &XBOFSWin::WinUsbDevice::winUsbDeviceInfo, this, &WinUsbDeviceTabWidget::handleWinUsbDeviceInfo);
    connect(winUsbDevice, &XBOFSWin::WinUsbDevice::winUsbDeviceInit, this, &WinUsbDeviceTabWidget::handleWinUsbDeviceInit);
    connect(winUsbDevice, &XBOFSWin::WinUsbDevice::winUsbDeviceInitComplete, this, &WinUsbDeviceTabWidget::handleWinUsbDeviceInitComplete);
    connect(winUsbDevice, &XBOFSWin::WinUsbDevice::winUsbDeviceReadingInput, this, &WinUsbDeviceTabWidget::handleWinUsbDeviceReadingInput);
    connect(winUsbDevice, &XBOFSWin::WinUsbDevice::winUsbDeviceTerminating, this, &WinUsbDeviceTabWidget::handleWinUsbDeviceTerminating);
    connect(winUsbDevice, &XBOFSWin::WinUsbDevice::winUsbDeviceError, this, &WinUsbDeviceTabWidget::handleWinUsbDeviceError);    
    connect(ui.bindingEnabledCheckBox, &QCheckBox::stateChanged, this, &WinUsbDeviceTabWidget::handleBindingEnabledCheckBoxStateChanged);
    connect(ui.configureBindingsButton, &QPushButton::clicked, this, &WinUsbDeviceTabWidget::handleConfigureBindingsPushButtonClicked);
    connect(ui.configureGuideDownBindingsButton, &QPushButton::clicked, this, &WinUsbDeviceTabWidget::handleConfigureGuideDownBindingsPushButtonClicked);
}

WinUsbDeviceTabWidget::~WinUsbDeviceTabWidget()
{
    delete configureBindingsDialog;
    delete configureGuideDownBindingsDialog;
}

void WinUsbDeviceTabWidget::handleVigEmConnect(const std::wstring &devicePath) {
    ui.vigEmClientStatus->setText(QString::fromUtf8("Connecting..."));
}

void WinUsbDeviceTabWidget::handleVigEmConnected(const std::wstring &devicePath) {
    ui.vigEmClientStatus->setText(QString::fromUtf8("Connected"));
}

void WinUsbDeviceTabWidget::handleVigEmTargetAdd(const std::wstring &devicePath) {    
    ui.vigEmTargetStatus->setText(QString::fromUtf8("Adding..."));
}

void WinUsbDeviceTabWidget::handleVigEmTargetAdded(const std::wstring &devicePath) {
    ui.vigEmTargetStatus->setText(QString::fromUtf8("Added")); // TODO: Display more details on target
}

void WinUsbDeviceTabWidget::handleVigEmTargetInfo(const std::wstring &devicePath, quint16 vendorId, quint16 productId, const ulong index) {
    ui.virtualDeviceVendorID->setText(QString::fromStdString(fmt::format("0x{:04X}", vendorId)));
    ui.virtualDeviceProductID->setText(QString::fromStdString(fmt::format("0x{:04X}", productId)));
    ui.virtualDeviceUserIndex->setText(QString::fromStdString(fmt::format("{}", index)));
}

void WinUsbDeviceTabWidget::handleVigEmError(const std::wstring &devicePath) {
    // TODO: Note error output in text area

}

void WinUsbDeviceTabWidget::handleWinUsbDeviceOpen(const std::wstring &devicePath) {
}

void WinUsbDeviceTabWidget::handleWinUsbDeviceInfo(const std::wstring &devicePath, quint16 vendorId, quint16 productId,
                                            const std::wstring &manufacturer, const std::wstring &product, const std::wstring &serialNumber) {
    ui.vendorIdLabel->setText(QString::fromStdString(fmt::format("0x{:04X}", vendorId)));
    ui.productIdLabel->setText(QString::fromStdString(fmt::format("0x{:04X}", productId)));
    ui.manufacturerLabel->setText(QString::fromStdWString(manufacturer));
    ui.productLabel->setText(QString::fromStdWString(product));
    ui.serialNumberLabel->setText(QString::fromStdWString(serialNumber));    
}

void WinUsbDeviceTabWidget::handleWinUsbDeviceOpened(const std::wstring &devicePath) {
}

void WinUsbDeviceTabWidget::handleWinUsbDeviceInit(const std::wstring &devicePath) {
}

void WinUsbDeviceTabWidget::handleWinUsbDeviceInitComplete(const std::wstring &devicePath) {
}

void WinUsbDeviceTabWidget::handleWinUsbDeviceReadingInput(const std::wstring &devicePath) {
    ui.winUsbDeviceStatus->setText(QString::fromUtf8("Reading input..."));
}

void WinUsbDeviceTabWidget::handleWinUsbDeviceTerminating(const std::wstring &devicePath) {
}

void WinUsbDeviceTabWidget::handleWinUsbDeviceError(const std::wstring &devicePath) { 
    // TODO: Note error output in text area
}

void WinUsbDeviceTabWidget::handleBindingEnabledCheckBoxStateChanged(int state) {
    ui.configureBindingsButton->setEnabled((bool)state);
    ui.configureGuideDownBindingsButton->setEnabled((bool)state);
}

void WinUsbDeviceTabWidget::handleConfigureBindingsPushButtonClicked(bool checked) {
    auto result = configureBindingsDialog->exec();
}

void WinUsbDeviceTabWidget::handleConfigureGuideDownBindingsPushButtonClicked(bool checked) {
    auto result = configureGuideDownBindingsDialog->exec();
}
