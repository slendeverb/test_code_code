#pragma once
#include "ui_demo_qt.h"
#include <bits/stdc++.h>
#include <QMainWindow>
#include <QDebug>
#include <QtCharts/QtCharts>
#include <QPainter>

class demo_qt : public QMainWindow {
    Q_OBJECT
    
public:
    demo_qt(QWidget* parent = nullptr);
    ~demo_qt();

private:
    Ui_demo_qt* ui;
    virtual void paintEvent(QPaintEvent *event) override;
};