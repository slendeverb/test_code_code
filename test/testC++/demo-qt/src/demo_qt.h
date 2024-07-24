#pragma once
#include "ui_demo_qt.h"
#include <QMainWindow>
#include <iostream>
#include <QDebug>

class demo_qt : public QMainWindow {
    Q_OBJECT
    
public:
    demo_qt(QWidget* parent = nullptr);
    ~demo_qt();

private:
    Ui_demo_qt* ui;
};