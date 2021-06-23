#pragma once

#include <QDialog>
#include "ui_ControlBindingDialog.h"

class ControlBindingDialog : public QDialog
{
    Q_OBJECT

public:
    ControlBindingDialog(QWidget *parent);
    ~ControlBindingDialog();

protected:
    Ui::ControlBindingDialog ui;
};
