#include "ControlBindingDialog.h"

ControlBindingDialog::ControlBindingDialog(QWidget *parent)
    : QDialog(parent)
{
    ui.setupUi(this);
    setModal(true);
}

ControlBindingDialog::~ControlBindingDialog()
{
}
