#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_XBOFSWinQT5GUI.h"

class XBOFSWinQT5GUI : public QMainWindow
{
    Q_OBJECT

public:
    XBOFSWinQT5GUI(QWidget *parent = Q_NULLPTR);

private:
    Ui::XBOFSWinQT5GUIClass ui;
};
