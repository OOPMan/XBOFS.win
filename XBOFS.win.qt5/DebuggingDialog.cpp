#include "DebuggingDialog.h"

DebuggingDialog::DebuggingDialog(QWidget *parent)
    : QDialog(parent)
{
    setModal(false);
    ui.setupUi(this);
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
}

DebuggingDialog::~DebuggingDialog()
{
}
