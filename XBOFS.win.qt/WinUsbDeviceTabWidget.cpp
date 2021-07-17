#include <qinputdialog.h>
#include <qmessagebox.h>

#include "WinUsbDeviceTabWidget.h"

WinUsbDeviceTabWidget::WinUsbDeviceTabWidget(
    QWidget *parent, QString devicePath, const XBOFSWin::WinUsbDevice *winUsbDevice, std::shared_ptr<spdlog::logger> logger
)
: QWidget(parent), winUsbDevice(winUsbDevice), logger(logger)
{
    configureBindingsDialog = new ConfigureBindingsDialog(this);
    debuggingDialog = new DebuggingDialog(winUsbDevice, this);
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
    connect(ui.activeProfileComboBox, &QComboBox::currentIndexChanged, this, &WinUsbDeviceTabWidget::handleActiveProfileComboBoxCurrentIndexChanged);
    connect(ui.addProfileButton, &QPushButton::clicked, this, &WinUsbDeviceTabWidget::handleAddProfilePushButtonClicked);
    connect(ui.deleteProfileButton, &QPushButton::clicked, this, &WinUsbDeviceTabWidget::handleDeleteProfilePushButtonClicked);
    connect(ui.configureBindingsButton, &QPushButton::clicked, this, &WinUsbDeviceTabWidget::handleConfigureBindingsPushButtonClicked);
    connect(ui.configureAlternateBindingsButton, &QPushButton::clicked, this, &WinUsbDeviceTabWidget::handleConfigureAlternateBindingsPushButtonClicked);
    connect(ui.guideButtonBehaviourComboBox, &QComboBox::currentIndexChanged, this, &WinUsbDeviceTabWidget::handleGuideButtonBehaviourComboBoxCurrentIndexChanged);
    connect(ui.debuggingEnabledCheckBox, &QCheckBox::stateChanged, this, &WinUsbDeviceTabWidget::handleDebuggingEnabledCheckBoxStateChanged);
    connect(ui.openDebuggingDialogPushButton, &QPushButton::clicked, this, &WinUsbDeviceTabWidget::handleOpenDebuggingDialogPushButtonClicked);
    connect(configureBindingsDialog, &QDialog::finished, this, [&](int result) { emit settingsChanged(); });
}

WinUsbDeviceTabWidget::~WinUsbDeviceTabWidget()
{
    delete configureBindingsDialog;
    delete debuggingDialog;
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
    while (settings.group() != "") settings.endGroup();
    settings.beginGroup(QString("%1/%2/%3").arg(this->vendorId, this->productId, this->serialNumber));
    auto profiles = settings.childGroups();
    auto activeProfile = settings.value(ACTIVE_PROFILE, "").toString();
    for (QStringList::const_iterator profileIterator = profiles.constBegin(); profileIterator != profiles.constEnd(); ++profileIterator) {
        auto profileName = *profileIterator;
        auto deletedKey = QString("%1/%2").arg(profileName, DELETED);
        if (!settings.value(deletedKey, true).toBool()) ui.activeProfileComboBox->addItem(profileName);
    }
    ui.activeProfileComboBox->setCurrentText(activeProfile);
    ui.vendorIdLabel->setText(this->vendorId);
    ui.productIdLabel->setText(this->productId);
    ui.manufacturerLabel->setText(this->vendorName);
    ui.productLabel->setText(this->productName);
    ui.serialNumberLabel->setText(this->serialNumber);    
    ui.bindingEnabledCheckBox->setEnabled(true);
    ui.bindingEnabledCheckBox->setChecked(settings.value(BINDING_ENABLED, false).toBool());
    ui.debuggingEnabledCheckBox->setEnabled(true);
    ui.debuggingEnabledCheckBox->setChecked(settings.value(DEBUG_ENABLED, false).toBool());
    ui.openDebuggingDialogPushButton->setEnabled(ui.debuggingEnabledCheckBox->isChecked());
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
    settings.setValue(BINDING_ENABLED, (bool)state);
    ui.bindingProfileGroupBox->setEnabled((bool)state);
    ui.activeProfileComboBox->setEnabled((bool)state);
    emit settingsChanged();
}

void WinUsbDeviceTabWidget::handleDebuggingEnabledCheckBoxStateChanged(int state) {
    settings.setValue(DEBUG_ENABLED, (bool)state);
    ui.openDebuggingDialogPushButton->setEnabled((bool)state);
    emit settingsChanged();
}

void WinUsbDeviceTabWidget::handleActiveProfileComboBoxCurrentIndexChanged(int index) {
    auto enabled = index > -1;
    auto activeProfile = ui.activeProfileComboBox->currentText();
    auto guideButtonBehaviourKey = QString("%1/%2").arg(activeProfile, GUIDE_BUTTON_MODE);
    ui.configureBindingsButton->setEnabled(enabled);
    ui.configureAlternateBindingsButton->setEnabled(enabled);
    ui.guideButtonBehaviourComboBox->setEnabled(enabled);
    ui.guideButtonBehaviourComboBox->setCurrentIndex(settings.value(guideButtonBehaviourKey, 0).toInt());
    settings.setValue(ACTIVE_PROFILE, activeProfile);    
    emit settingsChanged();
}

void WinUsbDeviceTabWidget::handleAddProfilePushButtonClicked(bool checked) {
    bool ok;
    QString profileName = QInputDialog::getText(this, "Add Profile", "Profile Name", QLineEdit::Normal, "", &ok);
    if (profileName.length() > 255) profileName.resize(255);
    if (ok && !profileName.isEmpty() && ui.activeProfileComboBox->findText(profileName) == -1) {
        ui.activeProfileComboBox->addItem(profileName);
        auto profileDeletedKey = QString("%1/%2").arg(profileName, DELETED);
        auto guideButtonBehaviourKey = QString("%1/%2").arg(profileName, GUIDE_BUTTON_MODE);
        settings.setValue(profileDeletedKey, false);
        settings.setValue(guideButtonBehaviourKey, 0);
        emit settingsChanged();
    }
}

void WinUsbDeviceTabWidget::handleDeleteProfilePushButtonClicked(bool checked) {
    if (!ui.activeProfileComboBox->count()) return;
    auto response = QMessageBox::question(this, APPLICATION, "Are you sure?");
    if (response == QMessageBox::Yes) {
        auto activeProfile = ui.activeProfileComboBox->currentText();
        auto profileDeletedKey = QString("%1/%2").arg(activeProfile, DELETED);
        settings.setValue(profileDeletedKey, true);
        ui.activeProfileComboBox->removeItem(ui.activeProfileComboBox->currentIndex());
        emit settingsChanged();
    }
}

void WinUsbDeviceTabWidget::handleConfigureBindingsPushButtonClicked(bool checked) {
    auto activeProfile = ui.activeProfileComboBox->currentText();
    configureBindingsDialog->open(vendorId, productId, productName, serialNumber, activeProfile, false);
}

void WinUsbDeviceTabWidget::handleConfigureAlternateBindingsPushButtonClicked(bool checked) {
    auto activeProfile = ui.activeProfileComboBox->currentText();
    configureBindingsDialog->open(vendorId, productId, productName, serialNumber, activeProfile, true);
}

void WinUsbDeviceTabWidget::handleGuideButtonBehaviourComboBoxCurrentIndexChanged(int index)
{
    auto activeProfile = ui.activeProfileComboBox->currentText();
    auto guideButtonBehaviourKey = QString("%1/%2").arg(activeProfile, GUIDE_BUTTON_MODE);
    settings.setValue(guideButtonBehaviourKey, index);
    emit settingsChanged();
}

void WinUsbDeviceTabWidget::handleOpenDebuggingDialogPushButtonClicked(bool checked) {
    debuggingDialog->open();
}
