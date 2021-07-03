#pragma once

#include <QDialog>
#include "ui_DebuggingDialog.h"
#include "ui_DebuggingWidget.h"
#include "ui_ControlBindingWidget.h"

class DebuggingDialog : public QDialog
{
    Q_OBJECT

public:
    DebuggingDialog(QWidget *parent);
    ~DebuggingDialog();

protected:
    Ui::DebuggingDialog ui;
    Ui::DebuggingWidget inputDataUi;
    Ui::ControlBindingWidget outputDataUi;
};
