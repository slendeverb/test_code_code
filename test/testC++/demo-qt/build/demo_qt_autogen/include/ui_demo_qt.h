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
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_demo_qt
{
public:
    QWidget *centralwidget;
    QPushButton *pushButton;
    QStatusBar *statusbar;
    QMenuBar *menuBar;
    QMenu *menudemo_qt;

    void setupUi(QMainWindow *demo_qt)
    {
        if (demo_qt->objectName().isEmpty())
            demo_qt->setObjectName(QString::fromUtf8("demo_qt"));
        demo_qt->resize(800, 600);
        centralwidget = new QWidget(demo_qt);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(340, 270, 93, 28));
        demo_qt->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(demo_qt);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        demo_qt->setStatusBar(statusbar);
        menuBar = new QMenuBar(demo_qt);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 800, 26));
        menudemo_qt = new QMenu(menuBar);
        menudemo_qt->setObjectName(QString::fromUtf8("menudemo_qt"));
        demo_qt->setMenuBar(menuBar);

        menuBar->addAction(menudemo_qt->menuAction());

        retranslateUi(demo_qt);

        QMetaObject::connectSlotsByName(demo_qt);
    } // setupUi

    void retranslateUi(QMainWindow *demo_qt)
    {
        demo_qt->setWindowTitle(QCoreApplication::translate("demo_qt", "demo_qt", nullptr));
        pushButton->setText(QCoreApplication::translate("demo_qt", "PushButton", nullptr));
        menudemo_qt->setTitle(QCoreApplication::translate("demo_qt", "demo_qt", nullptr));
    } // retranslateUi

};

namespace Ui {
    class demo_qt: public Ui_demo_qt {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DEMO_QT_H
