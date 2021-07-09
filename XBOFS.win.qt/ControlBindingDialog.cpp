#include "ControlBindingDialog.h"

ControlBindingDialog::ControlBindingDialog(QWidget *parent)
    : QDialog(parent)
{
    ui.setupUi(this);
    controlBindingWidget.setupUi(ui.controlPanelWidget);
    ui.controlPanelWidget->setEnabled(false);
    checkboxes = std::unordered_map<QCheckBox*, XUSB_BUTTON> {
        {controlBindingWidget.dPadUpCheckBox, XUSB_GAMEPAD_DPAD_UP},
        {controlBindingWidget.dPadDownCheckBox, XUSB_GAMEPAD_DPAD_DOWN},
        {controlBindingWidget.dPadLeftCheckBox, XUSB_GAMEPAD_DPAD_LEFT},
        {controlBindingWidget.dPadRightCheckBox, XUSB_GAMEPAD_DPAD_RIGHT},
        {controlBindingWidget.xButtonCheckBox, XUSB_GAMEPAD_X},
        {controlBindingWidget.yButtonCheckBox, XUSB_GAMEPAD_Y},
        {controlBindingWidget.aButtonCheckBox, XUSB_GAMEPAD_A},
        {controlBindingWidget.bButtonCheckBox, XUSB_GAMEPAD_B},
        {controlBindingWidget.leftBumperCheckBox, XUSB_GAMEPAD_LEFT_SHOULDER},
        {controlBindingWidget.rightBumperCheckBox, XUSB_GAMEPAD_RIGHT_SHOULDER},
        {controlBindingWidget.leftAnalogButtonCheckBox, XUSB_GAMEPAD_LEFT_THUMB},
        {controlBindingWidget.rightAnalogButtonCheckBox, XUSB_GAMEPAD_RIGHT_THUMB},
        {controlBindingWidget.startButtonCheckBox, XUSB_GAMEPAD_START},
        {controlBindingWidget.viewButtonCheckBox, XUSB_GAMEPAD_BACK},
        {controlBindingWidget.guideButtonCheckBox, XUSB_GAMEPAD_GUIDE}
    };
    setModal(true);
    connect(ui.bindCheckBox, &QCheckBox::stateChanged, this, &ControlBindingDialog::handleBindCheckBoxStateChanged);
    connect(controlBindingWidget.minLeftAnalogXaxisPushButton, &QPushButton::clicked, this, [=](bool c) { controlBindingWidget.leftAnalogXaxisSpinBox->setValue(-32768);  });
    connect(controlBindingWidget.zeroLeftAnalogXaxisPushButton, &QPushButton::clicked, this, [=](bool c) { controlBindingWidget.leftAnalogXaxisSpinBox->setValue(0);  });
    connect(controlBindingWidget.maxLeftAnalogXaxisPushButton, &QPushButton::clicked, this, [=](bool c) { controlBindingWidget.leftAnalogXaxisSpinBox->setValue(32767);  });
    connect(controlBindingWidget.minLeftAnalogYaxisPushButton, &QPushButton::clicked, this, [=](bool c) { controlBindingWidget.leftAnalogYaxisSpinBox->setValue(-32768);  });
    connect(controlBindingWidget.zeroLeftAnalogYaxisPushButton, &QPushButton::clicked, this, [=](bool c) { controlBindingWidget.leftAnalogYaxisSpinBox->setValue(0);  });
    connect(controlBindingWidget.maxLeftAnalogYaxisPushButton, &QPushButton::clicked, this, [=](bool c) { controlBindingWidget.leftAnalogYaxisSpinBox->setValue(32767);  });
    connect(controlBindingWidget.minRightAnalogXaxisPushButton, &QPushButton::clicked, this, [=](bool c) { controlBindingWidget.rightAnalogXaxisSpinBox->setValue(-32768);  });
    connect(controlBindingWidget.zeroRightAnalogXaxisPushButton, &QPushButton::clicked, this, [=](bool c) { controlBindingWidget.rightAnalogXaxisSpinBox->setValue(0);  });
    connect(controlBindingWidget.maxRightAnalogXaxisPushButton, &QPushButton::clicked, this, [=](bool c) { controlBindingWidget.rightAnalogXaxisSpinBox->setValue(32767);  });
    connect(controlBindingWidget.minRightAnalogYaxisPushButton, &QPushButton::clicked, this, [=](bool c) { controlBindingWidget.rightAnalogYaxisSpinBox->setValue(-32768);  });
    connect(controlBindingWidget.zeroRightAnalogYaxisPushButton, &QPushButton::clicked, this, [=](bool c) { controlBindingWidget.rightAnalogYaxisSpinBox->setValue(0);  });
    connect(controlBindingWidget.maxRightAnalogYaxisPushButton, &QPushButton::clicked, this, [=](bool c) { controlBindingWidget.rightAnalogYaxisSpinBox->setValue(32767);  });
}

ControlBindingDialog::~ControlBindingDialog()
{
}

void ControlBindingDialog::accept() {
    settings.setValue(BIND_ENABLED, ui.bindCheckBox->isChecked());
    settings.setValue(LEFT_TRIGGER, controlBindingWidget.leftTriggerStrengthSpinBox->value());
    settings.setValue(RIGHT_TRIGGER, controlBindingWidget.rightTriggerStrengthSpinBox->value());
    settings.setValue(THUMB_LX, controlBindingWidget.leftAnalogXaxisSpinBox->value());
    settings.setValue(THUMB_LY, controlBindingWidget.leftAnalogYaxisSpinBox->value());
    settings.setValue(THUMB_RX, controlBindingWidget.rightAnalogXaxisSpinBox->value());
    settings.setValue(THUMB_RY, controlBindingWidget.rightAnalogYaxisSpinBox->value());
    int buttons = 0;
    for (auto& [checkbox, value] : checkboxes) {
        if (checkbox->isChecked()) buttons |= value;
    }
    settings.setValue(BUTTONS, buttons);
    QDialog::accept();
}

void ControlBindingDialog::open(QString vendorId, QString productId, QString product, QString serialNumber, QString profile, bool alternativeBindings, XBOFSWin::XBO_ARCADE_STICK_BUTTONS button) {
    auto buttonName = buttonNames.at(button);
    while (settings.group() != "") settings.endGroup();
    auto group = QString("%1/%2/%3/%4/%5/%6").arg(vendorId, productId, serialNumber, profile, QString::number(alternativeBindings), QString::number((int)button));
    settings.beginGroup(group);    
    auto prefix = QString(alternativeBindings ? "Alternative Binding": "Binding");
    setWindowTitle(QString("%1: Configuring %2 for %3").arg(APPLICATION, prefix, buttonName));
    ui.bindCheckBox->setChecked(settings.value(BIND_ENABLED, false).toBool());
    controlBindingWidget.leftTriggerStrengthSpinBox->setValue(settings.value(LEFT_TRIGGER, 0).toInt());
    controlBindingWidget.rightTriggerStrengthSpinBox->setValue(settings.value(RIGHT_TRIGGER, 0).toInt());
    controlBindingWidget.leftAnalogXaxisSpinBox->setValue(settings.value(THUMB_LX, 0).toInt());
    controlBindingWidget.leftAnalogYaxisSpinBox->setValue(settings.value(THUMB_LY, 0).toInt());
    controlBindingWidget.rightAnalogXaxisSpinBox->setValue(settings.value(THUMB_RX, 0).toInt());
    controlBindingWidget.rightAnalogYaxisSpinBox->setValue(settings.value(THUMB_RY, 0).toInt());
    auto buttons = settings.value(BUTTONS, 0).toInt();
    for (auto& [checkbox, value] : checkboxes) {
        checkbox->setChecked(buttons & value);
    }
    QDialog::open();
}



void ControlBindingDialog::handleBindCheckBoxStateChanged(int state) {
    ui.controlPanelWidget->setEnabled((bool)state);
}

