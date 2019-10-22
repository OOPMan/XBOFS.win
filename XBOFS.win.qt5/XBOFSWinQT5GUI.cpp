#include "XBOFSWinQT5GUI.h"
#include <vector>
#include <spdlog/sinks/null_sink.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include <qthread.h>
#include <fmt/core.h>
#include <XBOFS.win/utils.h>
#include <XBOFS.win/WinUsbDeviceManager.h>

XBOFSWinQT5GUI::XBOFSWinQT5GUI(QWidget *parent)
: QMainWindow(parent)
{    
    ui.setupUi(this);      
    // Configure logging
    auto sinks = std::vector<spdlog::sink_ptr>();    
    auto rotatingFileSink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>("xbofs.win.qt5.log", 1024 * 1024 * 10, 10);
    sinks.push_back(rotatingFileSink);
    logger = XBOFSWin::get_logger("XBOFSWin QT5 GUI", sinks);
    spdlog::set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%t] [%n] [%l] %v");
    logger->info("Logging initialised");
    // Start WinUsbDeviceManager    
    winUsbDeviceManagerThread = new QThread();
    winUsbDeviceManager = new XBOFSWin::WinUsbDeviceManager(XBOFSWin::get_logger("WinUsbDeviceManager", sinks));
    connect(winUsbDeviceManagerThread, &QThread::finished, winUsbDeviceManager, &QObject::deleteLater);
    connect(winUsbDeviceManagerThread, &QThread::started, winUsbDeviceManager, &XBOFSWin::WinUsbDeviceManager::run);
    connect(winUsbDeviceManager, &XBOFSWin::WinUsbDeviceManager::winUsbDeviceManagerScanning, this, &XBOFSWinQT5GUI::handleWinUsbDeviceManagerScanning);
    connect(winUsbDeviceManager, &XBOFSWin::WinUsbDeviceManager::winUsbDeviceAdded, this, &XBOFSWinQT5GUI::handleWinUsbDeviceAdded);
    connect(winUsbDeviceManager, &XBOFSWin::WinUsbDeviceManager::winUsbDeviceRemoved, this, &XBOFSWinQT5GUI::handleWinUsbDeviceRemoved);
    connect(this, &XBOFSWinQT5GUI::destroyed, this, &XBOFSWinQT5GUI::handleTerminateWinUsbDeviceManager);
    winUsbDeviceManager->moveToThread(winUsbDeviceManagerThread);
    winUsbDeviceManagerThread->start();      
}

std::optional<std::pair<int, std::vector<std::tuple<std::wstring, QWidget*, Ui::WinUsbDeviceWidget*>>::iterator>> XBOFSWinQT5GUI::getIteratorForDevicePath(const std::wstring &devicePath) {
    auto iterator = tabs.begin();
    int index;
    for (index = 1; iterator != tabs.end(); index++) {
        auto currentDevicePath = std::get<0>(*iterator);
        if (currentDevicePath == devicePath) break;
        ++iterator;
    }
    if (iterator == tabs.end()) return std::nullopt;
    return std::optional<std::pair<int, std::vector<std::tuple<std::wstring, QWidget*, Ui::WinUsbDeviceWidget*>>::iterator>>{std::make_pair(index, iterator)};
}

void XBOFSWinQT5GUI::handleWinUsbDeviceAdded(const std::wstring &devicePath, const XBOFSWin::WinUsbDevice *winUsbDevice) {        
    // Connect signals    
    connect(winUsbDevice, &XBOFSWin::WinUsbDevice::vigEmConnect, this, &XBOFSWinQT5GUI::handleVigEmConnect);
    connect(winUsbDevice, &XBOFSWin::WinUsbDevice::vigEmConnected, this, &XBOFSWinQT5GUI::handleVigEmConnected);
    connect(winUsbDevice, &XBOFSWin::WinUsbDevice::vigEmTargetAdd, this, &XBOFSWinQT5GUI::handleVigEmTargetAdd);
    connect(winUsbDevice, &XBOFSWin::WinUsbDevice::vigEmTargetAdded, this, &XBOFSWinQT5GUI::handleVigEmTargetAdded);
    connect(winUsbDevice, &XBOFSWin::WinUsbDevice::vigEmError, this, &XBOFSWinQT5GUI::handleVigEmError);
    connect(winUsbDevice, &XBOFSWin::WinUsbDevice::winUsbDeviceOpen, this, &XBOFSWinQT5GUI::handleWinUsbDeviceOpen);
    connect(winUsbDevice, &XBOFSWin::WinUsbDevice::winUsbDeviceOpened, this, &XBOFSWinQT5GUI::handleWinUsbDeviceOpened);
    connect(winUsbDevice, &XBOFSWin::WinUsbDevice::winUsbDeviceInfo, this, &XBOFSWinQT5GUI::handleWinUsbDeviceInfo);
    connect(winUsbDevice, &XBOFSWin::WinUsbDevice::winUsbDeviceInit, this, &XBOFSWinQT5GUI::handleWinUsbDeviceInit);
    connect(winUsbDevice, &XBOFSWin::WinUsbDevice::winUsbDeviceInitComplete, this, &XBOFSWinQT5GUI::handleWinUsbDeviceInitComplete);
    connect(winUsbDevice, &XBOFSWin::WinUsbDevice::winUsbDeviceReadingInput, this, &XBOFSWinQT5GUI::handleWinUsbDeviceReadingInput);
    connect(winUsbDevice, &XBOFSWin::WinUsbDevice::winUsbDeviceTerminating, this, &XBOFSWinQT5GUI::handleWinUsbDeviceTerminating);
    connect(winUsbDevice, &XBOFSWin::WinUsbDevice::winUsbDeviceError, this, &XBOFSWinQT5GUI::handleWinUsbDeviceError);
    // Update UI    
    auto devicePathQString = QString::fromStdWString(devicePath);
    auto tabWidget = new QWidget();
    auto tabWidgetUi = new Ui::WinUsbDeviceWidget();
    tabWidget->setObjectName(devicePathQString);
    tabWidgetUi->setupUi(tabWidget);    
    auto tabIndex = ui.tabWidget->addTab(tabWidget, QString());    
    ui.tabWidget->setTabText(tabIndex, QString::fromStdWString(fmt::format(L"Stick {}", tabIndex)));
    tabs.push_back(std::make_tuple(devicePath, tabWidget, tabWidgetUi));
}

void XBOFSWinQT5GUI::handleWinUsbDeviceRemoved(const std::wstring &devicePath) {    
    auto optionalIterator = getIteratorForDevicePath(devicePath);
    if (!optionalIterator) return;
    auto tuple = *optionalIterator;
    auto index = tuple.first;
    auto iterator = tuple.second;
    auto tabWidget = std::get<1>(*iterator);
    auto tabWidgetUi = std::get<2>(*iterator);
    tabs.erase(iterator);
    ui.tabWidget->removeTab(index);
    delete tabWidget;
    delete tabWidgetUi;
    for (auto idx = 1; idx < ui.tabWidget->count(); idx++) {
        ui.tabWidget->setTabText(idx, QString::fromStdWString(fmt::format(L"Stick {}", idx)));
    }
}

void XBOFSWinQT5GUI::handleVigEmConnect(const std::wstring &devicePath) {
    auto optionalIterator = getIteratorForDevicePath(devicePath);
    if (!optionalIterator) return;
    auto iterator = (*optionalIterator).second;
    auto tabWidgetUi = std::get<2>(*iterator);
    tabWidgetUi->vigEmClientStatus->setText(QString::fromUtf8("Connecting..."));
}

void XBOFSWinQT5GUI::handleVigEmConnected(const std::wstring &devicePath) {
    auto optionalIterator = getIteratorForDevicePath(devicePath);
    if (!optionalIterator) return;
    auto iterator = (*optionalIterator).second;
    auto tabWidgetUi = std::get<2>(*iterator);
    tabWidgetUi->vigEmClientStatus->setText(QString::fromUtf8("Connected"));
}

void XBOFSWinQT5GUI::handleVigEmTargetAdd(const std::wstring &devicePath) {    
    auto optionalIterator = getIteratorForDevicePath(devicePath);
    if (!optionalIterator) return;
    auto iterator = (*optionalIterator).second;
    auto tabWidgetUi = std::get<2>(*iterator);
    tabWidgetUi->vigEmTargetStatus->setText(QString::fromUtf8("Adding..."));
}

void XBOFSWinQT5GUI::handleVigEmTargetAdded(const std::wstring &devicePath) {
    auto optionalIterator = getIteratorForDevicePath(devicePath);
    if (!optionalIterator) return;
    auto iterator = (*optionalIterator).second;
    auto tabWidgetUi = std::get<2>(*iterator);
    tabWidgetUi->vigEmTargetStatus->setText(QString::fromUtf8("Added")); // TODO: Display more details on target
}

void XBOFSWinQT5GUI::handleVigEmError(const std::wstring &devicePath) {
    // TODO: Note error output in text area
}

void XBOFSWinQT5GUI::handleWinUsbDeviceOpen(const std::wstring &devicePath) {
}

void XBOFSWinQT5GUI::handleWinUsbDeviceInfo(const std::wstring &devicePath, quint16 vendorId, quint16 productId,
                                            const std::wstring &manufacturer, const std::wstring &product, const std::wstring &serialNumber) {
    auto optionalIterator = getIteratorForDevicePath(devicePath);
    if (!optionalIterator) return;
    auto iterator = (*optionalIterator).second;
    auto tabWidgetUi = std::get<2>(*iterator);
    tabWidgetUi->vendorIdLabel->setText(QString::fromStdString(fmt::format("0x{:04X}", vendorId)));
    tabWidgetUi->productIdLabel->setText(QString::fromStdString(fmt::format("0x{:04X}", productId)));
    tabWidgetUi->manufacturerLabel->setText(QString::fromStdWString(manufacturer));
    tabWidgetUi->productLabel->setText(QString::fromStdWString(product));
    tabWidgetUi->serialNumberLabel->setText(QString::fromStdWString(serialNumber));    
}

void XBOFSWinQT5GUI::handleWinUsbDeviceOpened(const std::wstring &devicePath) {
}

void XBOFSWinQT5GUI::handleWinUsbDeviceInit(const std::wstring &devicePath) {
}

void XBOFSWinQT5GUI::handleWinUsbDeviceInitComplete(const std::wstring &devicePath) {
}

void XBOFSWinQT5GUI::handleWinUsbDeviceReadingInput(const std::wstring &devicePath) {
    auto optionalIterator = getIteratorForDevicePath(devicePath);
    if (!optionalIterator) return;
    auto iterator = (*optionalIterator).second;
    auto tabWidgetUi = std::get<2>(*iterator);
    tabWidgetUi->winUsbDeviceStatus->setText(QString::fromUtf8("Reading input..."));
}

void XBOFSWinQT5GUI::handleWinUsbDeviceTerminating(const std::wstring &devicePath) {
}

void XBOFSWinQT5GUI::handleWinUsbDeviceError(const std::wstring &devicePath) { 
    // TODO: Note error output in text area
}

void XBOFSWinQT5GUI::handleWinUsbDeviceManagerScanning() {
    ui.winUsbDeviceManagerStatus->setText(QString::fromUtf8("Scanning for supported controllers..."));
}

void XBOFSWinQT5GUI::handleTerminateWinUsbDeviceManager() {    
    logger->info("Requesting interruption of thread handling WinUsbDeviceManager");
    winUsbDeviceManagerThread->requestInterruption();
    logger->info("Signalling thread handling WinUsbDeviceManager to terminate");
    winUsbDeviceManagerThread->terminate();
    logger->info("Waiting for thread hanlding WinUsbDeviceManager to terminate");
    winUsbDeviceManagerThread->wait();
    logger->flush();
}