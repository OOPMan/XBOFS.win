#pragma once

#include <XBOFS.win/constants.h>
#include <QDialog>
#include <qsettings.h>
#include "ui_ControlBindingDialog.h"
#include "ui_ControlBindingWidget.h"

using namespace XBOFSWin::settings;

const std::unordered_map<XBOFSWin::XBO_ARCADE_STICK_BUTTONS, QString> buttonNames {
    {XBOFSWin::XBO_ARCADE_STICK_BUTTONS::STICK_UP, QString("Stick Up")},
    {XBOFSWin::XBO_ARCADE_STICK_BUTTONS::STICK_DOWN, QString("Stick Down")},
    {XBOFSWin::XBO_ARCADE_STICK_BUTTONS::STICK_LEFT, QString("Stick Left")},
    {XBOFSWin::XBO_ARCADE_STICK_BUTTONS::STICK_RIGHT, QString("Stick Right")},
    {XBOFSWin::XBO_ARCADE_STICK_BUTTONS::X, QString("X Button")},
    {XBOFSWin::XBO_ARCADE_STICK_BUTTONS::Y, QString("Y Button")},
    {XBOFSWin::XBO_ARCADE_STICK_BUTTONS::A, QString("A Button")},
    {XBOFSWin::XBO_ARCADE_STICK_BUTTONS::B, QString("B Button")},
    {XBOFSWin::XBO_ARCADE_STICK_BUTTONS::RB, QString("RB Button")},
    {XBOFSWin::XBO_ARCADE_STICK_BUTTONS::RT, QString("RT Button")},
    {XBOFSWin::XBO_ARCADE_STICK_BUTTONS::LB, QString("LB Button")},
    {XBOFSWin::XBO_ARCADE_STICK_BUTTONS::LT, QString("LT Button")},
    {XBOFSWin::XBO_ARCADE_STICK_BUTTONS::VIEW, QString("View Button")},
    {XBOFSWin::XBO_ARCADE_STICK_BUTTONS::START, QString("Start Button")},
    {XBOFSWin::XBO_ARCADE_STICK_BUTTONS::GUIDE, QString("Guide Button")}
};

class ControlBindingDialog : public QDialog
{
    Q_OBJECT

public:
    ControlBindingDialog(QWidget *parent);
    ~ControlBindingDialog();

public slots:
    void accept();
    void open(QString vendorId, QString productId, QString product, QString serialNumber, QString profile, bool alternativeBindings, XBOFSWin::XBO_ARCADE_STICK_BUTTONS button);
    void handleBindCheckBoxStateChanged(int state);

protected:
    QSettings settings = QSettings(ORGANIZATION, APPLICATION);
    Ui::ControlBindingDialog ui;
    Ui::ControlBindingWidget controlBindingWidget;
    std::unordered_map<QCheckBox*, XUSB_BUTTON> checkboxes;
};
