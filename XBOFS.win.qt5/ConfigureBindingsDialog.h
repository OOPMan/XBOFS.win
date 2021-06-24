#pragma once

#include <QDialog>
#include <qsettings.h>
#include <spdlog/spdlog.h>
#include "ui_ConfigureBindingsDialog.h"
#include "ControlBindingDialog.h"

class ConfigureBindingsDialog : public QDialog
{
    Q_OBJECT

public:
    ConfigureBindingsDialog(QSettings *settings, QWidget *parent);
    ~ConfigureBindingsDialog();

public slots:
    void open(QString vendorId, QString productId, QString product, QString serialNumber, bool guideDown);
    void handleStickUpPushButtonClicked(bool checked = false);
    void handleStickDownPushButtonClicked(bool checked = false);
    void handleStickLeftPushButtonClicked(bool checked = false);
    void handleStickRightPushButtonClicked(bool checked = false);
    void handleXButtonPushButtonClicked(bool checked = false);
    void handleYButtonPushButtonClicked(bool checked = false);
    void handleAButtonPushButtonClicked(bool checked = false);
    void handleBButtonPushButtonClicked(bool checked = false);
    void handleRBButtonPushButtonClicked(bool checked = false);
    void handleRTButtonPushButtonClicked(bool checked = false);
    void handleLBButtonPushButtonClicked(bool checked = false);
    void handleLTButtonPushButtonClicked(bool checked = false);
    void handleViewButtonPushButtonClicked(bool checked = false);
    void handleStartButtonPushButtonClicked(bool checked = false);

protected:    
    QSettings* settings;
    QString vendorId;
    QString productId;
    QString product;
    QString serialNumber;    
    bool guideDown; 
    Ui::ConfigureBindingsDialog ui;
    ControlBindingDialog* controlBindingDialog;
};