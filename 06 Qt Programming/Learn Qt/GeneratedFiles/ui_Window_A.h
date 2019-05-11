/********************************************************************************
** Form generated from reading UI file 'Window_A.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WINDOW_A_H
#define UI_WINDOW_A_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Window_AClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Window_AClass)
    {
        if (Window_AClass->objectName().isEmpty())
            Window_AClass->setObjectName(QString::fromUtf8("Window_AClass"));
        Window_AClass->resize(600, 400);
        menuBar = new QMenuBar(Window_AClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        Window_AClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Window_AClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        Window_AClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(Window_AClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        Window_AClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(Window_AClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        Window_AClass->setStatusBar(statusBar);

        retranslateUi(Window_AClass);

        QMetaObject::connectSlotsByName(Window_AClass);
    } // setupUi

    void retranslateUi(QMainWindow *Window_AClass)
    {
        Window_AClass->setWindowTitle(QCoreApplication::translate("Window_AClass", "Window_A", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Window_AClass: public Ui_Window_AClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WINDOW_A_H
