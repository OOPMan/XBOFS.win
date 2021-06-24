#include "ConfigureBindingsDialog.h"

ConfigureBindingsDialog::ConfigureBindingsDialog(QSettings *settings, QWidget *parent)
    : QDialog(parent), settings(settings)
{
    controlBindingDialog = new ControlBindingDialog(this);
    ui.setupUi(this);
    setModal(true);
    connect(ui.stickUpPushButton, &QPushButton::clicked, this, &ConfigureBindingsDialog::handleStickUpPushButtonClicked);
}

ConfigureBindingsDialog::~ConfigureBindingsDialog()
{
    delete controlBindingDialog;
}

void ConfigureBindingsDialog::open(QString vendorId, QString productId, QString product, QString serialNumber, bool guideDown) {
    this->vendorId = vendorId;
    this->productId = productId;
    this->product = product;
    this->serialNumber = serialNumber;
    this->guideDown = guideDown;
    auto prefix = QString(guideDown ? "Guide Down Bindings": "Bindings");
    setWindowTitle(QString("Configuring %1 for %2 (S/N: %3)").arg(prefix, product, serialNumber));
    QDialog::open();
}

void ConfigureBindingsDialog::handleStickUpPushButtonClicked(bool checked) {
    controlBindingDialog->open();
}

void ConfigureBindingsDialog::handleStickDownPushButtonClicked(bool checked) {
    controlBindingDialog->open();
}

void ConfigureBindingsDialog::handleStickLeftPushButtonClicked(bool checked) {
    controlBindingDialog->open();
}

void ConfigureBindingsDialog::handleStickRightPushButtonClicked(bool checked) {
    controlBindingDialog->open();
}

void ConfigureBindingsDialog::handleXButtonPushButtonClicked(bool checked) {
    controlBindingDialog->open();
}

void ConfigureBindingsDialog::handleYButtonPushButtonClicked(bool checked) {
    controlBindingDialog->open();
}

void ConfigureBindingsDialog::handleAButtonPushButtonClicked(bool checked) {
    controlBindingDialog->open();
}

void ConfigureBindingsDialog::handleBButtonPushButtonClicked(bool checked) {
    controlBindingDialog->open();
}

void ConfigureBindingsDialog::handleRBButtonPushButtonClicked(bool checked) {
    controlBindingDialog->open();
}

void ConfigureBindingsDialog::handleRTButtonPushButtonClicked(bool checked) {
    controlBindingDialog->open();
}

void ConfigureBindingsDialog::handleLBButtonPushButtonClicked(bool checked) {
    controlBindingDialog->open();
}

void ConfigureBindingsDialog::handleLTButtonPushButtonClicked(bool checked) {
    controlBindingDialog->open();
}

void ConfigureBindingsDialog::handleViewButtonPushButtonClicked(bool checked) {
    controlBindingDialog->open();
}

void ConfigureBindingsDialog::handleStartButtonPushButtonClicked(bool checked) {
    controlBindingDialog->open();
}
