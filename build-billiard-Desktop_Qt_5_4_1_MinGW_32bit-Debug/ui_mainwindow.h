/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>
#include "myglwidget.h"

QT_BEGIN_NAMESPACE

class Ui_CGPraktikum2
{
public:
    QWidget *centralWidget;
    MyGLWidget *widget;

    void setupUi(QMainWindow *CGPraktikum2)
    {
        if (CGPraktikum2->objectName().isEmpty())
            CGPraktikum2->setObjectName(QStringLiteral("CGPraktikum2"));
        CGPraktikum2->resize(685, 480);
        centralWidget = new QWidget(CGPraktikum2);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidget->setMinimumSize(QSize(0, 0));
        widget = new MyGLWidget(centralWidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(20, 20, 651, 451));
        CGPraktikum2->setCentralWidget(centralWidget);

        retranslateUi(CGPraktikum2);

        QMetaObject::connectSlotsByName(CGPraktikum2);
    } // setupUi

    void retranslateUi(QMainWindow *CGPraktikum2)
    {
        CGPraktikum2->setWindowTitle(QApplication::translate("CGPraktikum2", "MainWindow", 0));
    } // retranslateUi

};

namespace Ui {
    class CGPraktikum2: public Ui_CGPraktikum2 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
