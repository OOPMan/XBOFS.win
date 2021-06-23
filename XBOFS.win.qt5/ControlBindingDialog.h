#pragma once

#include <QDialog>
#include "ui_ControlBindingDialog.h"
#include "ui_ControlBindingWidget.h"

class ControlBindingDialog : public QDialog
{
    Q_OBJECT

public:
    ControlBindingDialog(QWidget *parent);
    ~ControlBindingDialog();

public slots:
    void handleBindCheckBoxStateChanged(int state);

protected:
    Ui::ControlBindingDialog ui;
    Ui::ControlBindingWidget controlBindingWidget;
};
