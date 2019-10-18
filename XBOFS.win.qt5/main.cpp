#include <string>
#include <QtWidgets/QApplication>
#include <qmetatype.h>

#include "XBOFSWinQT5GUI.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qRegisterMetaType<std::wstring>();    
    XBOFSWinQT5GUI w;
    w.show();
    return a.exec();
}
