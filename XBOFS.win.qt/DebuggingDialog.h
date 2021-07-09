#pragma once

#include <chrono>
#include <limits>
#include <QDialog>
#include <XBOFS.win/WinUsbDevice.h>
#include "ui_DebuggingDialog.h"
#include "ui_DebuggingWidget.h"
#include "ui_ControlBindingWidget.h"

class DebuggingDialog : public QDialog
{
    Q_OBJECT

public:
    DebuggingDialog(const XBOFSWin::WinUsbDevice* winUsbDevice, QWidget* parent);
    ~DebuggingDialog();

public slots:
    void handleDebugInfoLoopTime(const std::chrono::microseconds& loopTime);
    void handleDebugInfoButtons(
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
    );
    void handleDebugInfoXUSB_REPORT(
        const USHORT wButtons,
        const BYTE   bLeftTrigger,
        const BYTE   bRightTrigger,
        const SHORT  sThumbLX,
        const SHORT  sThumbLY,
        const SHORT  sThumbRX,
        const SHORT  sThumbRY
    );

protected:
    Ui::DebuggingDialog ui;
    Ui::DebuggingWidget inputDataUi;
    Ui::ControlBindingWidget outputDataUi;

    std::chrono::microseconds lastLoopTime = std::chrono::microseconds(0);
    std::chrono::microseconds worstLoopTime = std::chrono::microseconds(std::numeric_limits<long long>::min());
    std::chrono::microseconds bestLoopTime = std::chrono::microseconds(std::numeric_limits<long long>::max());
    std::chrono::microseconds averageLoopTime = std::chrono::microseconds(0);
    std::chrono::microseconds accumulatedLoopTime = std::chrono::microseconds(0);
    unsigned long long loopCount = 0;
};
