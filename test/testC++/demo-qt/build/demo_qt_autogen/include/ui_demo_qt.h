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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_demo_qt
{
public:
    QWidget *centralwidget;
    QLabel *clientLabel;
    QLabel *serverAddressLabel;
    QLineEdit *serverAddressLineEdit;
    QLabel *serverPortLabel;
    QLineEdit *serverPortLineEdit;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *connectButton;
    QSpacerItem *horizontalSpacer;
    QPushButton *cancelButton;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *demo_qt)
    {
        if (demo_qt->objectName().isEmpty())
            demo_qt->setObjectName(QString::fromUtf8("demo_qt"));
        demo_qt->resize(900, 602);
        centralwidget = new QWidget(demo_qt);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        centralwidget->setAutoFillBackground(false);
        centralwidget->setStyleSheet(QString::fromUtf8("background-color: white;"));
        clientLabel = new QLabel(centralwidget);
        clientLabel->setObjectName(QString::fromUtf8("clientLabel"));
        clientLabel->setGeometry(QRect(410, 110, 111, 50));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(20);
        clientLabel->setFont(font);
        serverAddressLabel = new QLabel(centralwidget);
        serverAddressLabel->setObjectName(QString::fromUtf8("serverAddressLabel"));
        serverAddressLabel->setGeometry(QRect(150, 220, 141, 31));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(serverAddressLabel->sizePolicy().hasHeightForWidth());
        serverAddressLabel->setSizePolicy(sizePolicy);
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font1.setPointSize(16);
        serverAddressLabel->setFont(font1);
        serverAddressLineEdit = new QLineEdit(centralwidget);
        serverAddressLineEdit->setObjectName(QString::fromUtf8("serverAddressLineEdit"));
        serverAddressLineEdit->setGeometry(QRect(330, 220, 391, 31));
        serverPortLabel = new QLabel(centralwidget);
        serverPortLabel->setObjectName(QString::fromUtf8("serverPortLabel"));
        serverPortLabel->setGeometry(QRect(120, 320, 161, 31));
        serverPortLabel->setFont(font1);
        serverPortLineEdit = new QLineEdit(centralwidget);
        serverPortLineEdit->setObjectName(QString::fromUtf8("serverPortLineEdit"));
        serverPortLineEdit->setGeometry(QRect(330, 320, 391, 31));
        horizontalLayoutWidget = new QWidget(centralwidget);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(260, 420, 401, 80));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        connectButton = new QPushButton(horizontalLayoutWidget);
        connectButton->setObjectName(QString::fromUtf8("connectButton"));
        QFont font2;
        font2.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font2.setPointSize(10);
        connectButton->setFont(font2);

        horizontalLayout->addWidget(connectButton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        cancelButton = new QPushButton(horizontalLayoutWidget);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));
        cancelButton->setFont(font2);

        horizontalLayout->addWidget(cancelButton);

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
        clientLabel->setText(QCoreApplication::translate("demo_qt", "\345\256\242\346\210\267\347\253\257", nullptr));
        serverAddressLabel->setText(QCoreApplication::translate("demo_qt", "\346\234\215\345\212\241\345\231\250\345\234\260\345\235\200", nullptr));
        serverPortLabel->setText(QCoreApplication::translate("demo_qt", "\346\234\215\345\212\241\345\231\250\347\253\257\345\217\243\345\217\267", nullptr));
        connectButton->setText(QCoreApplication::translate("demo_qt", "\350\277\236\346\216\245", nullptr));
        cancelButton->setText(QCoreApplication::translate("demo_qt", "\345\217\226\346\266\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class demo_qt: public Ui_demo_qt {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DEMO_QT_H
