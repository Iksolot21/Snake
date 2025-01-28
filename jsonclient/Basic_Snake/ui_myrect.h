/********************************************************************************
** Form generated from reading UI file 'myrect.ui'
**
** Created by: Qt User Interface Compiler version 6.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYRECT_H
#define UI_MYRECT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MyRect
{
public:
    QWidget *centralwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MyRect)
    {
        if (MyRect->objectName().isEmpty())
            MyRect->setObjectName("MyRect");
        MyRect->resize(800, 600);
        centralwidget = new QWidget(MyRect);
        centralwidget->setObjectName("centralwidget");
        MyRect->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MyRect);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 25));
        MyRect->setMenuBar(menubar);
        statusbar = new QStatusBar(MyRect);
        statusbar->setObjectName("statusbar");
        MyRect->setStatusBar(statusbar);

        retranslateUi(MyRect);

        QMetaObject::connectSlotsByName(MyRect);
    } // setupUi

    void retranslateUi(QMainWindow *MyRect)
    {
        MyRect->setWindowTitle(QCoreApplication::translate("MyRect", "MyRect", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MyRect: public Ui_MyRect {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYRECT_H
