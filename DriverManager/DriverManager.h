#pragma once
#include <libwdi/libwdi.h>
#include <QtWidgets/QMainWindow>
#include "ui_DriverManager.h"

class DriverManager : public QMainWindow
{
    Q_OBJECT

public:
    DriverManager(QWidget *parent = Q_NULLPTR);

public slots:
    void handleRazerAtroxXBODriverPushButtonClicked(bool checked = false);
    void handleMadcatzTE2XBODriverPushButtonClicked(bool checked = false);
    void handleVictrixProFSXBODriverPushButtonClicked(bool checked = false);

protected:
    Ui::DriverManagerClass ui;

    int installDriver(QString driverName, unsigned short vendorId, unsigned short productId);
};
