#include "WinUsbDeviceTabWidget.h"

WinUsbDeviceTabWidget::WinUsbDeviceTabWidget(
    QWidget *parent, QString devicePath, const XBOFSWin::WinUsbDevice *winUsbDevice, QSettings *settings, std::shared_ptr<spdlog::logger> logger
)
: QWidget(parent), winUsbDevice(winUsbDevice), settings(settings), logger(logger)
{
    configureBindingsDialog = new ConfigureBindingsDialog(settings, this);
    configureGuideDownBindingsDialog = new ConfigureBindingsDialog(settings, this);
    setObjectName(devicePath);
    ui.setupUi(this);
    connect(this, &WinUsbDeviceTabWidget::settingsChanged, winUsbDevice, &XBOFSWin::WinUsbDevice::refreshSettings);
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
    connect(ui.debuggingEnabledCheckBox, &QCheckBox::stateChanged, this, &WinUsbDeviceTabWidget::handleDebuggingEnabledCheckBoxStateChanged);
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
    ui.vigEmTargetStatus->setText(QString::fromUtf8("Added"));
}

void WinUsbDeviceTabWidget::handleVigEmTargetInfo(const std::wstring &devicePath, quint16 vendorId, quint16 productId, const ulong index) {
    ui.virtualDeviceVendorID->setText(QString::fromStdString(fmt::format("0x{:04X}", vendorId)));
    ui.virtualDeviceProductID->setText(QString::fromStdString(fmt::format("0x{:04X}", productId)));
    ui.virtualDeviceUserIndex->setText(QString::fromStdString(fmt::format("{}", index)));
}

void WinUsbDeviceTabWidget::handleVigEmError(const std::wstring &devicePath) {
    ui.vigEmTargetStatus->setText(QString::fromUtf8("Error!"));
}
    
void WinUsbDeviceTabWidget::handleWinUsbDeviceInfo(const std::wstring &devicePath, const QString &vendorId, const QString &vendorName,
                                                   const QString &productId, const QString &productName, const QString &serialNumber) {
    this->vendorId = vendorId;
    this->vendorName = vendorName;
    this->productId = productId;
    this->productName = productName;
    this->serialNumber = serialNumber;
    this->settingsKey = QString("%1/%2/%3").arg(this->vendorId, this->productId, this->serialNumber);
    ui.vendorIdLabel->setText(this->vendorId);
    ui.productIdLabel->setText(this->productId);
    ui.manufacturerLabel->setText(this->vendorName);
    ui.productLabel->setText(this->productName);
    ui.serialNumberLabel->setText(this->serialNumber);    
    ui.bindingEnabledCheckBox->setEnabled(true);
    ui.bindingEnabledCheckBox->setChecked(settings->value(QString("%1/%2").arg(settingsKey, "binding"), false).toBool());
    ui.debuggingEnabledCheckBox->setEnabled(true);
    ui.debuggingEnabledCheckBox->setChecked(settings->value(QString("%1/%2").arg(settingsKey, "debug"), false).toBool());
}

void WinUsbDeviceTabWidget::handleWinUsbDeviceOpen(const std::wstring &devicePath) {
    ui.winUsbDeviceStatus->setText(QString::fromUtf8("Opening..."));
}

void WinUsbDeviceTabWidget::handleWinUsbDeviceOpened(const std::wstring &devicePath) {
    ui.winUsbDeviceStatus->setText(QString::fromUtf8("Open"));
}

void WinUsbDeviceTabWidget::handleWinUsbDeviceInit(const std::wstring &devicePath) {
    ui.winUsbDeviceStatus->setText(QString::fromUtf8("Init"));
}

void WinUsbDeviceTabWidget::handleWinUsbDeviceInitComplete(const std::wstring &devicePath) {
    ui.winUsbDeviceStatus->setText(QString::fromUtf8("Init complete"));
}

void WinUsbDeviceTabWidget::handleWinUsbDeviceReadingInput(const std::wstring &devicePath) {
    ui.winUsbDeviceStatus->setText(QString::fromUtf8("Reading input..."));
}

void WinUsbDeviceTabWidget::handleWinUsbDeviceTerminating(const std::wstring &devicePath) {
    ui.winUsbDeviceStatus->setText(QString::fromUtf8("Terminating..."));
}

void WinUsbDeviceTabWidget::handleWinUsbDeviceError(const std::wstring &devicePath) { 
    ui.winUsbDeviceStatus->setText(QString::fromUtf8("Error!"));
}

void WinUsbDeviceTabWidget::handleBindingEnabledCheckBoxStateChanged(int state) {
    settings->setValue(QString("%1/%2").arg(settingsKey, "binding"), (bool)state);
    ui.configureBindingsButton->setEnabled((bool)state);
    ui.configureGuideDownBindingsButton->setEnabled((bool)state);
    logger->info("Notifying device to refresh settings");
    emit settingsChanged();
}

void WinUsbDeviceTabWidget::handleDebuggingEnabledCheckBoxStateChanged(int state) {
    settings->setValue(QString("%1/%2").arg(settingsKey, "debug"), (bool)state);
    // TODO: Display/hide debugging info
    logger->info("Notifying device to refresh settings");
    emit settingsChanged();
}

void WinUsbDeviceTabWidget::handleConfigureBindingsPushButtonClicked(bool checked) {
    configureBindingsDialog->open(vendorId, productId, productName, serialNumber, false);
}

void WinUsbDeviceTabWidget::handleConfigureGuideDownBindingsPushButtonClicked(bool checked) {
    configureGuideDownBindingsDialog->open(vendorId, productId, productName, serialNumber, true);
}
