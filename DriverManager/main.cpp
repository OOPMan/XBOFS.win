#include "DriverManager.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);
    DriverManager mainWindow;
    mainWindow.show();
    return application.exec();
}
