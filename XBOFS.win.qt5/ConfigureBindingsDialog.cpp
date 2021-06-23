#include "ConfigureBindingsDialog.h"

ConfigureBindingsDialog::ConfigureBindingsDialog(QWidget *parent)
    : QDialog(parent)
{
    controlBindingDialog = new ControlBindingDialog(this);
    ui.setupUi(this);
    setModal(true);
    connect(ui.stickUpPushButton, &QPushButton::clicked, this, &ConfigureBindingsDialog::handleStickUpPushButtonClicked);
}

ConfigureBindingsDialog::~ConfigureBindingsDialog()
{
    delete controlBindingDialog;
}


void ConfigureBindingsDialog::handleStickUpPushButtonClicked(bool checked) {
    auto result = controlBindingDialog->exec();
}
