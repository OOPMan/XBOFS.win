#include "XBOFSWinQT5GUI.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    XBOFSWinQT5GUI w;
    w.show();
    return a.exec();
}
