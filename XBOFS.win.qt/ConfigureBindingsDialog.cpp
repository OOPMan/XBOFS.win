#include "ConfigureBindingsDialog.h"

ConfigureBindingsDialog::ConfigureBindingsDialog(QWidget *parent)
    : QDialog(parent)
{
    controlBindingDialog = new ControlBindingDialog(this);
    ui.setupUi(this);
    setModal(true);
    connect(ui.stickUpPushButton,       &QPushButton::clicked, this, &ConfigureBindingsDialog::handleStickUpPushButtonClicked);
    connect(ui.stickDownPushButton,     &QPushButton::clicked, this, &ConfigureBindingsDialog::handleStickDownPushButtonClicked);
    connect(ui.stickLeftPushButton,     &QPushButton::clicked, this, &ConfigureBindingsDialog::handleStickLeftPushButtonClicked);
    connect(ui.stickRightPushButton,    &QPushButton::clicked, this, &ConfigureBindingsDialog::handleStickRightPushButtonClicked);
    connect(ui.xButtonPushButton,       &QPushButton::clicked, this, &ConfigureBindingsDialog::handleXButtonPushButtonClicked);
    connect(ui.yButtonPushButton,       &QPushButton::clicked, this, &ConfigureBindingsDialog::handleYButtonPushButtonClicked);
    connect(ui.aButtonPushButton,       &QPushButton::clicked, this, &ConfigureBindingsDialog::handleAButtonPushButtonClicked);
    connect(ui.bButtonPushButton,       &QPushButton::clicked, this, &ConfigureBindingsDialog::handleBButtonPushButtonClicked);
    connect(ui.rbButtonPushButton,      &QPushButton::clicked, this, &ConfigureBindingsDialog::handleRBButtonPushButtonClicked);
    connect(ui.rtButtonPushButton,      &QPushButton::clicked, this, &ConfigureBindingsDialog::handleRTButtonPushButtonClicked);
    connect(ui.lbButtonPushButton,      &QPushButton::clicked, this, &ConfigureBindingsDialog::handleLBButtonPushButtonClicked);
    connect(ui.ltButtonPushButton,      &QPushButton::clicked, this, &ConfigureBindingsDialog::handleLTButtonPushButtonClicked);
    connect(ui.viewButtonPushButton,    &QPushButton::clicked, this, &ConfigureBindingsDialog::handleViewButtonPushButtonClicked);
    connect(ui.startButtonPushButton,   &QPushButton::clicked, this, &ConfigureBindingsDialog::handleStartButtonPushButtonClicked);
}

ConfigureBindingsDialog::~ConfigureBindingsDialog()
{
    delete controlBindingDialog;
}

void ConfigureBindingsDialog::open(QString vendorId, QString productId, QString product, QString serialNumber, QString profile, bool alternativeBindings) {
    this->vendorId = vendorId;
    this->productId = productId;
    this->product = product;
    this->serialNumber = serialNumber;
    this->profile = profile;
    this->alternativeBindings = alternativeBindings;
    auto prefix = QString(alternativeBindings ? "Alternative Bindings": "Bindings");
    setWindowTitle(QString("%1: Configuring %2 for %3 (S/N: %4)").arg(APPLICATION, prefix, product, serialNumber));
    QDialog::open();
}

void ConfigureBindingsDialog::handleStickUpPushButtonClicked(bool checked) {
    controlBindingDialog->open(vendorId, productId, product, serialNumber, profile, alternativeBindings, XBOFSWin::XBO_ARCADE_STICK_BUTTONS::STICK_UP);
}

void ConfigureBindingsDialog::handleStickDownPushButtonClicked(bool checked) {
    controlBindingDialog->open(vendorId, productId, product, serialNumber, profile, alternativeBindings, XBOFSWin::XBO_ARCADE_STICK_BUTTONS::STICK_DOWN);
}

void ConfigureBindingsDialog::handleStickLeftPushButtonClicked(bool checked) {
    controlBindingDialog->open(vendorId, productId, product, serialNumber, profile, alternativeBindings, XBOFSWin::XBO_ARCADE_STICK_BUTTONS::STICK_LEFT);
}

void ConfigureBindingsDialog::handleStickRightPushButtonClicked(bool checked) {
    controlBindingDialog->open(vendorId, productId, product, serialNumber, profile, alternativeBindings, XBOFSWin::XBO_ARCADE_STICK_BUTTONS::STICK_RIGHT);
}

void ConfigureBindingsDialog::handleXButtonPushButtonClicked(bool checked) {
    controlBindingDialog->open(vendorId, productId, product, serialNumber, profile, alternativeBindings, XBOFSWin::XBO_ARCADE_STICK_BUTTONS::X);
}

void ConfigureBindingsDialog::handleYButtonPushButtonClicked(bool checked) {
    controlBindingDialog->open(vendorId, productId, product, serialNumber, profile, alternativeBindings, XBOFSWin::XBO_ARCADE_STICK_BUTTONS::Y);
}

void ConfigureBindingsDialog::handleAButtonPushButtonClicked(bool checked) {
    controlBindingDialog->open(vendorId, productId, product, serialNumber, profile, alternativeBindings, XBOFSWin::XBO_ARCADE_STICK_BUTTONS::A);
}

void ConfigureBindingsDialog::handleBButtonPushButtonClicked(bool checked) {
    controlBindingDialog->open(vendorId, productId, product, serialNumber, profile, alternativeBindings, XBOFSWin::XBO_ARCADE_STICK_BUTTONS::B);
}

void ConfigureBindingsDialog::handleRBButtonPushButtonClicked(bool checked) {
    controlBindingDialog->open(vendorId, productId, product, serialNumber, profile, alternativeBindings, XBOFSWin::XBO_ARCADE_STICK_BUTTONS::RB);
}

void ConfigureBindingsDialog::handleRTButtonPushButtonClicked(bool checked) {
    controlBindingDialog->open(vendorId, productId, product, serialNumber, profile, alternativeBindings, XBOFSWin::XBO_ARCADE_STICK_BUTTONS::RT);
}

void ConfigureBindingsDialog::handleLBButtonPushButtonClicked(bool checked) {
    controlBindingDialog->open(vendorId, productId, product, serialNumber, profile, alternativeBindings, XBOFSWin::XBO_ARCADE_STICK_BUTTONS::LB);
}

void ConfigureBindingsDialog::handleLTButtonPushButtonClicked(bool checked) {
    controlBindingDialog->open(vendorId, productId, product, serialNumber, profile, alternativeBindings, XBOFSWin::XBO_ARCADE_STICK_BUTTONS::LT);
}

void ConfigureBindingsDialog::handleViewButtonPushButtonClicked(bool checked) {
    controlBindingDialog->open(vendorId, productId, product, serialNumber, profile, alternativeBindings, XBOFSWin::XBO_ARCADE_STICK_BUTTONS::VIEW);
}

void ConfigureBindingsDialog::handleStartButtonPushButtonClicked(bool checked) {
    controlBindingDialog->open(vendorId, productId, product, serialNumber, profile, alternativeBindings, XBOFSWin::XBO_ARCADE_STICK_BUTTONS::START);
}
