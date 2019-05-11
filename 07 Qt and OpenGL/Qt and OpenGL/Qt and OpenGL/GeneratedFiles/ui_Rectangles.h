/********************************************************************************
** Form generated from reading UI file 'Rectangles.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RECTANGLES_H
#define UI_RECTANGLES_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RectanglesClass
{
public:

    void setupUi(QWidget *RectanglesClass)
    {
        if (RectanglesClass->objectName().isEmpty())
            RectanglesClass->setObjectName(QString::fromUtf8("RectanglesClass"));
        RectanglesClass->resize(600, 400);

        retranslateUi(RectanglesClass);

        QMetaObject::connectSlotsByName(RectanglesClass);
    } // setupUi

    void retranslateUi(QWidget *RectanglesClass)
    {
        RectanglesClass->setWindowTitle(QCoreApplication::translate("RectanglesClass", "Rectangles", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RectanglesClass: public Ui_RectanglesClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RECTANGLES_H
