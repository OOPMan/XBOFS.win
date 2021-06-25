#include "ControlBindingDialog.h"

ControlBindingDialog::ControlBindingDialog(QSettings *settings, QWidget *parent)
    : QDialog(parent), settings(settings)
{
    ui.setupUi(this);
    controlBindingWidget.setupUi(ui.controlPanelWidget);
    ui.controlPanelWidget->setEnabled(false);
    checkboxes = std::vector<QCheckBox*> {
        ui.bindCheckBox,
        controlBindingWidget.dPadUpCheckBox,
        controlBindingWidget.dPadDownCheckBox,
        controlBindingWidget.dPadLeftCheckBox,
        controlBindingWidget.dPadRightCheckBox,
        controlBindingWidget.yButtonCheckBox,
        controlBindingWidget.xButtonCheckBox,
        controlBindingWidget.aButtonCheckBox,
        controlBindingWidget.bButtonCheckBox,
        controlBindingWidget.rbButtonCheckBox,
        controlBindingWidget.rtButtonCheckBox,
        controlBindingWidget.lbButtonCheckBox,
        controlBindingWidget.ltButtonCheckBox,    
        controlBindingWidget.viewButtonCheckBox,
        controlBindingWidget.startButtonCheckBox,
        controlBindingWidget.guideButtonCheckBox,
        controlBindingWidget.leftThumbstickButtonCheckBox,
        controlBindingWidget.rightThumbstickButtonCheckBox
    };
    setModal(true);
    connect(ui.bindCheckBox, &QCheckBox::stateChanged, this, &ControlBindingDialog::handleBindCheckBoxStateChanged);
}

ControlBindingDialog::~ControlBindingDialog()
{
}

void ControlBindingDialog::accept() {
    settings->setValue(QString("%1/%2").arg(settingsKey, "bind"), ui.bindCheckBox->isChecked());
    for (auto& item : checkboxes) {
        auto keyName = QString("%1/%2").arg(settingsKey, item->text());
        settings->setValue(keyName, item->isChecked());
    }
    QDialog::accept();
}

void ControlBindingDialog::open(QString vendorId, QString productId, QString product, QString serialNumber, bool guideDown, XBOFSWin::XBO_ARCADE_STICK_BUTTONS button) {
    auto buttonName = buttonNames.at(button);
    this->settingsKey = QString("bindings/%1/%2/%3/%4/%5").arg(vendorId, productId, serialNumber, QString::number(guideDown), buttonName);
    this->vendorId = vendorId;
    this->productId = productId;
    this->product = product;
    this->serialNumber = serialNumber;
    this->guideDown = guideDown;
    this->button = button;
    auto prefix = QString(guideDown ? "Guide Down Binding": "Binding");
    setWindowTitle(QString("Configuring %1 for %2").arg(prefix, buttonName));
    for (auto& item : checkboxes) {
        auto keyName = QString("%1/%2").arg(settingsKey, item->text());
        item->setChecked(settings->value(keyName, false).toBool());
    }
    QDialog::open();
}



void ControlBindingDialog::handleBindCheckBoxStateChanged(int state) {
    ui.controlPanelWidget->setEnabled((bool)state);
}
