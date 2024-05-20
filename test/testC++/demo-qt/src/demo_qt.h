#pragma once
#include <QDebug>
#include <QMainWindow>
#include <iostream>
#include "ui_demo_qt.h"

class demo_qt : public QMainWindow {
    Q_OBJECT

   public:
    demo_qt(QWidget* parent = nullptr);
    ~demo_qt();

   private:
    Ui_demo_qt* ui;
};