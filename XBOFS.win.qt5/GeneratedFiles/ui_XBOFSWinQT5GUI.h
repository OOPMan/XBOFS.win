/********************************************************************************
** Form generated from reading UI file 'XBOFSWinQT5GUI.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XBOFSWINQT5GUI_H
#define UI_XBOFSWINQT5GUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_XBOFSWinQT5GUIClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *XBOFSWinQT5GUIClass)
    {
        if (XBOFSWinQT5GUIClass->objectName().isEmpty())
            XBOFSWinQT5GUIClass->setObjectName(QString::fromUtf8("XBOFSWinQT5GUIClass"));
        XBOFSWinQT5GUIClass->resize(600, 400);
        menuBar = new QMenuBar(XBOFSWinQT5GUIClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        XBOFSWinQT5GUIClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(XBOFSWinQT5GUIClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        XBOFSWinQT5GUIClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(XBOFSWinQT5GUIClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        XBOFSWinQT5GUIClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(XBOFSWinQT5GUIClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        XBOFSWinQT5GUIClass->setStatusBar(statusBar);

        retranslateUi(XBOFSWinQT5GUIClass);

        QMetaObject::connectSlotsByName(XBOFSWinQT5GUIClass);
    } // setupUi

    void retranslateUi(QMainWindow *XBOFSWinQT5GUIClass)
    {
        XBOFSWinQT5GUIClass->setWindowTitle(QCoreApplication::translate("XBOFSWinQT5GUIClass", "XBOFSWinQT5GUI", nullptr));
    } // retranslateUi

};

namespace Ui {
    class XBOFSWinQT5GUIClass: public Ui_XBOFSWinQT5GUIClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XBOFSWINQT5GUI_H
