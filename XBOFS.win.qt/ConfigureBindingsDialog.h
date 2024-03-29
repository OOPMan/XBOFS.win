#pragma once

#include <XBOFS.win/constants.h>
#include <QDialog>
#include <qsettings.h>
#include <spdlog/spdlog.h>
#include "ui_ConfigureBindingsDialog.h"
#include "ControlBindingDialog.h"

using namespace XBOFSWin::settings;

class ConfigureBindingsDialog : public QDialog
{
    Q_OBJECT

public:
    ConfigureBindingsDialog(QWidget *parent);
    ~ConfigureBindingsDialog();

public slots:
    void accept();
    void open(QString vendorId, QString productId, QString product, QString serialNumber, QString profile, bool alternativeBindings);
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
    void handleEnableSOCDCleaningCheckBoxStateChanged(int state);

protected:    
    QString vendorId;
    QString productId;
    QString product;
    QString serialNumber;    
    QString profile;
    bool alternativeBindings; 
    Ui::ConfigureBindingsDialog ui;
    ControlBindingDialog* controlBindingDialog;
    QSettings settings = QSettings(ORGANIZATION, APPLICATION);
};
