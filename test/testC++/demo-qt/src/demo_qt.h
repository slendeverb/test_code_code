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

class demo_qt : public QMainWindow {
    Q_OBJECT
    
public:
    demo_qt(QWidget* parent = nullptr);
    ~demo_qt();
    void keyPressEvent(QKeyEvent* k) override;
    void mousePressEvent(QMouseEvent* m) override;

private slots:
    void newActionSlot();
    void openActionSlot();
    void saveActionSlot();

private:
    Ui_demo_qt* ui;
};