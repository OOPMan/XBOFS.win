#include "DriverManager.h"
#include <SetupAPI.h>

DriverManager::DriverManager(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    connect(ui.razerAtroxXBODriverPushButton, &QPushButton::clicked, this, &DriverManager::handleRazerAtroxXBODriverPushButtonClicked);
    connect(ui.madcatzTE2DriverPushButton, &QPushButton::clicked, this, &DriverManager::handleMadcatzTE2XBODriverPushButtonClicked);
    connect(ui.victrixProFSXBODriverPushButton, &QPushButton::clicked, this, &DriverManager::handleVictrixProFSXBODriverPushButtonClicked);
}

int DriverManager::installDriver(QString driverName, unsigned short vendorId, unsigned short productId) 
{
    int result = WDI_SUCCESS;
    auto applicationFilePath = QApplication::applicationDirPath();
    auto defaultDirQString = QString("%1\\zadig_driver\\%2").arg(applicationFilePath.replace("/", "\\"), driverName);
    auto defaultDirStdString = defaultDirQString.toStdString();
    auto infNameStdString = QString("%1.inf").arg(driverName).toStdString(); 
    auto infName = infNameStdString.c_str();
    auto defaultDir = defaultDirStdString.c_str();
    struct wdi_options_install_driver installOptions = { 
        (HWND)winId() 
    };
    char deviceGUID[] = "{5ACF052A-3BE5-46AE-905E-356BA17671BD}";
    struct wdi_options_prepare_driver prepareOptions = { 
        0,
        NULL,
        deviceGUID
    };
    struct wdi_options_create_list cl_options = { 1 };
    struct wdi_device_info *device, *list = NULL;
    result = wdi_create_list(&list, &cl_options);
    if (result == (int)WDI_SUCCESS) {
        for (device = list; device != NULL; device = device->next) {
            if (device->vid != vendorId || device->pid != productId) continue;
            result = wdi_prepare_driver(device, defaultDir, infName, &prepareOptions);
            if (result == WDI_SUCCESS) {
                result = wdi_install_driver(device, defaultDir, infName, &installOptions);
            }
        }
    }
    wdi_destroy_list(list);    
    return result;
}

void DriverManager::handleRazerAtroxXBODriverPushButtonClicked(bool checked) 
{
    ui.diagnosticsLabel->setText(QString("libwdi Result Code: %1").arg(QString::number(installDriver("razer_atrox_xbo", 0x1532, 0x0A00))));
}

void DriverManager::handleMadcatzTE2XBODriverPushButtonClicked(bool checked) 
{
    ui.diagnosticsLabel->setText(QString("libwdi Result Code: %1").arg(QString::number(installDriver("madcatz_te2_xbo", 0x0738, 0x4a01))));
}

void DriverManager::handleVictrixProFSXBODriverPushButtonClicked(bool checked)
{
    ui.diagnosticsLabel->setText(QString("libwdi Result Code: %1").arg(QString::number(installDriver("victrix_pro_fs_xbo", 0xe6f, 0x205))));
}
