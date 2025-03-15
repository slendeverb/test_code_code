#pragma once
#include "ui_demo_qt.h"
#include <QMainWindow>
#include <QProcess>
#include <QButtonGroup>
#include <QMessageBox>
#include <QFileDialog>
#include <QDebug>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QtCharts>
#include <QTcpSocket>
#include <QHostAddress>

class demo_qt : public QMainWindow {
    Q_OBJECT
    
public:
    demo_qt(QWidget* parent = nullptr);
    ~demo_qt();

private slots:
    void onCancelButtonClicked();
    void onConnectButtonClicked();

private:
    Ui_demo_qt* ui;
    QTcpSocket* socket;
};