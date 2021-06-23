#pragma once

#include <QDialog>
#include "ui_ConfigureBindingsDialog.h"
#include "ControlBindingDialog.h"

class ConfigureBindingsDialog : public QDialog
{
    Q_OBJECT

public:
    ConfigureBindingsDialog(QWidget *parent);
    ~ConfigureBindingsDialog();

public slots:
    void handleStickUpPushButtonClicked(bool checked = false);

protected:    
    Ui::ConfigureBindingsDialog ui;
    ControlBindingDialog* controlBindingDialog;
};
