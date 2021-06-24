#include "ControlBindingDialog.h"

ControlBindingDialog::ControlBindingDialog(QSettings *settings, QWidget *parent)
    : QDialog(parent), settings(settings)
{
    ui.setupUi(this);
    controlBindingWidget.setupUi(ui.controlPanelWidget);
    ui.controlPanelWidget->setEnabled(false);
    setModal(true);
    connect(ui.bindCheckBox, &QCheckBox::stateChanged, this, &ControlBindingDialog::handleBindCheckBoxStateChanged);
}

ControlBindingDialog::~ControlBindingDialog()
{
}

void ControlBindingDialog::open(QString vendorId, QString productId, QString product, QString serialNumber, bool guideDown, XBOFSWin::XBO_ARCADE_STICK_BUTTONS button) {
    this->vendorId = vendorId;
    this->productId = productId;
    this->product = product;
    this->serialNumber = serialNumber;
    this->guideDown = guideDown;
    this->button = button;
    auto prefix = QString(guideDown ? "Guide Down Binding": "Binding");
    setWindowTitle(QString("Configuring %1 for %2").arg(prefix, buttonNames.at(button)));
    QDialog::open();
}



void ControlBindingDialog::handleBindCheckBoxStateChanged(int state) {
    ui.controlPanelWidget->setEnabled((bool)state);
}
