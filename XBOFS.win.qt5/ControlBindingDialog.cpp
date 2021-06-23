#include "ControlBindingDialog.h"

ControlBindingDialog::ControlBindingDialog(QWidget *parent)
    : QDialog(parent)
{
    ui.setupUi(this);
    controlBindingWidget.setupUi(ui.controlPanelWidget);
    ui.controlPanelWidget->setEnabled(false);
    setModal(true);
    connect(ui.bindCheckBox, &QCheckBox::stateChanged, this, &ControlBindingDialog::handleBindCheckBoxStateChanged);
}

ControlBindingDialog::~ControlBindingDialog()
{
}


void ControlBindingDialog::handleBindCheckBoxStateChanged(int state) {
    ui.controlPanelWidget->setEnabled((bool)state);
}
