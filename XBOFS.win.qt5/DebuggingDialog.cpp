#include "DebuggingDialog.h"

DebuggingDialog::DebuggingDialog(const XBOFSWin::WinUsbDevice *winUsbDevice, QWidget *parent)
    : QDialog(parent)
{
    setModal(false);
    ui.setupUi(this);
    // Configure
    ui.inputDataGroupBox->setAttribute(Qt::WA_TransparentForMouseEvents);
    ui.inputDataGroupBox->setFocusPolicy(Qt::NoFocus);
    ui.outputDataGroupBox->setAttribute(Qt::WA_TransparentForMouseEvents);
    ui.outputDataGroupBox->setFocusPolicy(Qt::NoFocus);    
    inputDataUi.setupUi(ui.inputDataWidget);
    outputDataUi.setupUi(ui.outputDataWidget);
    outputDataUi.minLeftAnalogXaxisPushButton->hide();
    outputDataUi.minLeftAnalogYaxisPushButton->hide();
    outputDataUi.minRightAnalogXaxisPushButton->hide();
    outputDataUi.minRightAnalogYaxisPushButton->hide();
    outputDataUi.zeroLeftAnalogXaxisPushButton->hide();
    outputDataUi.zeroLeftAnalogYaxisPushButton->hide();
    outputDataUi.zeroRightAnalogXaxisPushButton->hide();
    outputDataUi.zeroRightAnalogYaxisPushButton->hide();
    outputDataUi.maxLeftAnalogXaxisPushButton->hide();
    outputDataUi.maxLeftAnalogYaxisPushButton->hide();
    outputDataUi.maxRightAnalogXaxisPushButton->hide();
    outputDataUi.maxRightAnalogYaxisPushButton->hide();
    // Connect Signals
    connect(winUsbDevice, &XBOFSWin::WinUsbDevice::debugInfoLoopTime, this, &DebuggingDialog::handleDebugInfoLoopTime);
    connect(winUsbDevice, &XBOFSWin::WinUsbDevice::debugInfoButtons, this, &DebuggingDialog::handleDebugInfoButtons);
    connect(winUsbDevice, &XBOFSWin::WinUsbDevice::debugInfoXUSB_REPORT, this, &DebuggingDialog::handleDebugInfoXUSB_REPORT);
}

DebuggingDialog::~DebuggingDialog()
{
}

void DebuggingDialog::handleDebugInfoLoopTime(const std::chrono::microseconds &loopTime) 
{
    lastLoopTime = loopTime;
    if (loopTime > worstLoopTime) worstLoopTime = loopTime;
    if (loopTime < bestLoopTime) bestLoopTime = loopTime;
    loopCount += 1;
    accumulatedLoopTime += loopTime;
    averageLoopTime = accumulatedLoopTime / loopCount;
    ui.lastLoopTimeLabel->setText(QString("%1 microseconds").arg(lastLoopTime.count()));
    ui.worstLoopTimeLabel->setText(QString("%1 microseconds").arg(worstLoopTime.count()));
    ui.bestLoopTimeLabel->setText(QString("%1 microseconds").arg(bestLoopTime.count()));
    ui.averageLoopTimeLabel->setText(QString("%1 microseconds").arg(averageLoopTime.count()));
}

void DebuggingDialog::handleDebugInfoButtons(
    const bool& stickUp,
    const bool& stickDown,
    const bool& stickLeft,
    const bool& stickRight,
    const bool& x,
    const bool& y,
    const bool& a,
    const bool& b,
    const bool& rb,
    const bool& rt,
    const bool& lb,
    const bool& lt,
    const bool& view,
    const bool& start,
    const bool& guide
)
{
    inputDataUi.stickUpCheckBox->setChecked(stickUp);
    inputDataUi.stickDownCheckBox->setChecked(stickDown);
    inputDataUi.stickLeftCheckBox->setChecked(stickLeft);
    inputDataUi.stickRightCheckBox->setChecked(stickRight);
    inputDataUi.xCheckBox->setChecked(x);
    inputDataUi.yCheckBox->setChecked(y);
    inputDataUi.aCheckBox->setChecked(a);
    inputDataUi.bCheckBox->setChecked(b);
    inputDataUi.rbCheckBox->setChecked(rb);
    inputDataUi.rtCheckBox->setChecked(rt);
    inputDataUi.lbCheckBox->setChecked(lb);
    inputDataUi.ltCheckBox->setChecked(lt);
    inputDataUi.viewCheckBox->setChecked(view);
    inputDataUi.startCheckBox->setChecked(start);
    inputDataUi.guideCheckBox->setChecked(guide);
}


void DebuggingDialog::handleDebugInfoXUSB_REPORT(
    const USHORT wButtons,
    const BYTE   bLeftTrigger,
    const BYTE   bRightTrigger,
    const SHORT  sThumbLX,
    const SHORT  sThumbLY,
    const SHORT  sThumbRX,
    const SHORT  sThumbRY
)
{
    outputDataUi.dPadUpCheckBox->setChecked(wButtons & XUSB_GAMEPAD_DPAD_UP);
    outputDataUi.dPadDownCheckBox->setChecked(wButtons & XUSB_GAMEPAD_DPAD_DOWN);
    outputDataUi.dPadLeftCheckBox->setChecked(wButtons & XUSB_GAMEPAD_DPAD_LEFT);
    outputDataUi.dPadRightCheckBox->setChecked(wButtons & XUSB_GAMEPAD_DPAD_RIGHT);
    outputDataUi.xButtonCheckBox->setChecked(wButtons & XUSB_GAMEPAD_X);
    outputDataUi.yButtonCheckBox->setChecked(wButtons & XUSB_GAMEPAD_Y);
    outputDataUi.aButtonCheckBox->setChecked(wButtons & XUSB_GAMEPAD_A);
    outputDataUi.bButtonCheckBox->setChecked(wButtons & XUSB_GAMEPAD_B);
    outputDataUi.leftBumperCheckBox->setChecked(wButtons & XUSB_GAMEPAD_LEFT_SHOULDER);
    outputDataUi.rightBumperCheckBox->setChecked(wButtons & XUSB_GAMEPAD_RIGHT_SHOULDER);
    outputDataUi.leftAnalogButtonCheckBox->setChecked(wButtons & XUSB_GAMEPAD_LEFT_THUMB);
    outputDataUi.rightAnalogButtonCheckBox->setChecked(wButtons & XUSB_GAMEPAD_RIGHT_THUMB);
    outputDataUi.startButtonCheckBox->setChecked(wButtons & XUSB_GAMEPAD_START);
    outputDataUi.viewButtonCheckBox->setChecked(wButtons & XUSB_GAMEPAD_BACK);
    outputDataUi.leftTriggerStrengthSpinBox->setValue(bLeftTrigger);
    outputDataUi.rightTriggerStrengthSpinBox->setValue(bRightTrigger);
    outputDataUi.leftAnalogXaxisSpinBox->setValue(sThumbLX);
    outputDataUi.leftAnalogYaxisSpinBox->setValue(sThumbLY);
    outputDataUi.rightAnalogXaxisSpinBox->setValue(sThumbRX);
    outputDataUi.rightAnalogYaxisSpinBox->setValue(sThumbRY);
}

