/********************************************************************************
** Form generated from reading UI file 'demo_qt.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DEMO_QT_H
#define UI_DEMO_QT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_demo_qt
{
public:
    QWidget *centralwidget;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *demo_qt)
    {
        if (demo_qt->objectName().isEmpty())
            demo_qt->setObjectName(QString::fromUtf8("demo_qt"));
        demo_qt->resize(942, 618);
        centralwidget = new QWidget(demo_qt);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        centralwidget->setAutoFillBackground(false);
        centralwidget->setStyleSheet(QString::fromUtf8("background-color: white;"));
        demo_qt->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(demo_qt);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        demo_qt->setStatusBar(statusbar);

        retranslateUi(demo_qt);

        QMetaObject::connectSlotsByName(demo_qt);
    } // setupUi

    void retranslateUi(QMainWindow *demo_qt)
    {
        demo_qt->setWindowTitle(QCoreApplication::translate("demo_qt", "demo_qt", nullptr));
    } // retranslateUi

};

namespace Ui {
    class demo_qt: public Ui_demo_qt {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DEMO_QT_H
