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
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_demo_qt
{
public:
    QAction *newAction;
    QAction *openAction;
    QAction *saveAction;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QTextEdit *textEdit;
    QStatusBar *statusbar;
    QMenuBar *menuBar;
    QMenu *FileMenu;
    QMenu *compileMenu;
    QMenu *buildMenu;

    void setupUi(QMainWindow *demo_qt)
    {
        if (demo_qt->objectName().isEmpty())
            demo_qt->setObjectName(QString::fromUtf8("demo_qt"));
        demo_qt->resize(942, 618);
        newAction = new QAction(demo_qt);
        newAction->setObjectName(QString::fromUtf8("newAction"));
        openAction = new QAction(demo_qt);
        openAction->setObjectName(QString::fromUtf8("openAction"));
        saveAction = new QAction(demo_qt);
        saveAction->setObjectName(QString::fromUtf8("saveAction"));
        centralwidget = new QWidget(demo_qt);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        centralwidget->setAutoFillBackground(false);
        centralwidget->setStyleSheet(QString::fromUtf8("background-color: white;"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        textEdit = new QTextEdit(centralwidget);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));

        verticalLayout->addWidget(textEdit);

        demo_qt->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(demo_qt);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        demo_qt->setStatusBar(statusbar);
        menuBar = new QMenuBar(demo_qt);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 942, 26));
        FileMenu = new QMenu(menuBar);
        FileMenu->setObjectName(QString::fromUtf8("FileMenu"));
        compileMenu = new QMenu(menuBar);
        compileMenu->setObjectName(QString::fromUtf8("compileMenu"));
        buildMenu = new QMenu(menuBar);
        buildMenu->setObjectName(QString::fromUtf8("buildMenu"));
        demo_qt->setMenuBar(menuBar);

        menuBar->addAction(FileMenu->menuAction());
        menuBar->addAction(compileMenu->menuAction());
        menuBar->addAction(buildMenu->menuAction());
        FileMenu->addAction(newAction);
        FileMenu->addAction(openAction);
        FileMenu->addAction(saveAction);

        retranslateUi(demo_qt);

        QMetaObject::connectSlotsByName(demo_qt);
    } // setupUi

    void retranslateUi(QMainWindow *demo_qt)
    {
        demo_qt->setWindowTitle(QCoreApplication::translate("demo_qt", "demo_qt", nullptr));
        newAction->setText(QCoreApplication::translate("demo_qt", "\346\226\260\345\273\272(&N)", nullptr));
        openAction->setText(QCoreApplication::translate("demo_qt", "\346\211\223\345\274\200(&O)", nullptr));
        saveAction->setText(QCoreApplication::translate("demo_qt", "\345\217\246\345\255\230\344\270\272(&S)", nullptr));
        FileMenu->setTitle(QCoreApplication::translate("demo_qt", "\346\226\207\344\273\266(&F)", nullptr));
        compileMenu->setTitle(QCoreApplication::translate("demo_qt", "\347\274\226\350\257\221(&E)", nullptr));
        buildMenu->setTitle(QCoreApplication::translate("demo_qt", "\346\236\204\345\273\272(&B)", nullptr));
    } // retranslateUi

};

namespace Ui {
    class demo_qt: public Ui_demo_qt {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DEMO_QT_H
