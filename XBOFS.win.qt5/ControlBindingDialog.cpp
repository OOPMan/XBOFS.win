#include "ControlBindingDialog.h"

ControlBindingDialog::ControlBindingDialog(QWidget *parent)
    : QDialog(parent)
{
    ui.setupUi(this);
    controlBindingWidget.setupUi(ui.controlPanelWidget);
    ui.controlPanelWidget->setEnabled(false);
    checkboxes = std::unordered_map<XBOFSWin::XB360_CONTROL_BUTTONS, QCheckBox*> {
        {XBOFSWin::XB360_CONTROL_BUTTONS::DPAD_UP, controlBindingWidget.dPadUpCheckBox},
        {XBOFSWin::XB360_CONTROL_BUTTONS::DPAD_DOWN, controlBindingWidget.dPadDownCheckBox},
        {XBOFSWin::XB360_CONTROL_BUTTONS::DPAD_LEFT, controlBindingWidget.dPadLeftCheckBox},
        {XBOFSWin::XB360_CONTROL_BUTTONS::DPAD_RIGHT, controlBindingWidget.dPadRightCheckBox},
        {XBOFSWin::XB360_CONTROL_BUTTONS::Y, controlBindingWidget.yButtonCheckBox},
        {XBOFSWin::XB360_CONTROL_BUTTONS::X, controlBindingWidget.xButtonCheckBox},
        {XBOFSWin::XB360_CONTROL_BUTTONS::A, controlBindingWidget.aButtonCheckBox},
        {XBOFSWin::XB360_CONTROL_BUTTONS::B, controlBindingWidget.bButtonCheckBox},
        {XBOFSWin::XB360_CONTROL_BUTTONS::RB, controlBindingWidget.rbButtonCheckBox},
        {XBOFSWin::XB360_CONTROL_BUTTONS::RT, controlBindingWidget.rtButtonCheckBox},
        {XBOFSWin::XB360_CONTROL_BUTTONS::LB, controlBindingWidget.lbButtonCheckBox},
        {XBOFSWin::XB360_CONTROL_BUTTONS::LT, controlBindingWidget.ltButtonCheckBox},    
        {XBOFSWin::XB360_CONTROL_BUTTONS::VIEW, controlBindingWidget.viewButtonCheckBox},
        {XBOFSWin::XB360_CONTROL_BUTTONS::START, controlBindingWidget.startButtonCheckBox},
        {XBOFSWin::XB360_CONTROL_BUTTONS::GUIDE, controlBindingWidget.guideButtonCheckBox},
        {XBOFSWin::XB360_CONTROL_BUTTONS::THUMB_LEFT, controlBindingWidget.leftThumbstickButtonCheckBox},
        {XBOFSWin::XB360_CONTROL_BUTTONS::THUMB_RIGHT, controlBindingWidget.rightThumbstickButtonCheckBox},
    };
    setModal(true);
    connect(ui.bindCheckBox, &QCheckBox::stateChanged, this, &ControlBindingDialog::handleBindCheckBoxStateChanged);
}

ControlBindingDialog::~ControlBindingDialog()
{
}

void ControlBindingDialog::accept() {
    settings.setValue(QString("%1/bind").arg(settingsKey), ui.bindCheckBox->isChecked());
    for (auto& item : checkboxes) {
        auto keyName = QString("%1/%2").arg(settingsKey, QString::number(static_cast<int>(item.first)));
        settings.setValue(keyName, item.second->isChecked());
    }
    QDialog::accept();
}

void ControlBindingDialog::open(QString vendorId, QString productId, QString product, QString serialNumber, bool guideDown, XBOFSWin::XBO_ARCADE_STICK_BUTTONS button) {
    auto buttonName = buttonNames.at(button);
    settingsKey = QString("%1/%2/%3/%4/%5").arg(vendorId, productId, serialNumber, QString::number(guideDown), buttonName);
    this->vendorId = vendorId;
    this->productId = productId;
    this->product = product;
    this->serialNumber = serialNumber;
    this->guideDown = guideDown;
    this->button = button;
    auto prefix = QString(guideDown ? "Guide Down Binding": "Binding");
    setWindowTitle(QString("Configuring %1 for %2").arg(prefix, buttonName));
    for (auto& item : checkboxes) {
        auto keyName = QString("%1/%2").arg(settingsKey, QString::number(static_cast<int>(item.first)));
        item.second->setChecked(settings.value(keyName, false).toBool());
    }
    ui.bindCheckBox->setChecked(settings.value(QString("%1/bind").arg(settingsKey), false).toBool());
    QDialog::open();
}



void ControlBindingDialog::handleBindCheckBoxStateChanged(int state) {
    ui.controlPanelWidget->setEnabled((bool)state);
}

