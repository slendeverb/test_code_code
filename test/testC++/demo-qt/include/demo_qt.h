#pragma once
#include <QDebug>
#include <QMainWindow>
#include <QPainter>
#include <QtCharts/QtCharts>
#include "ui_demo_qt.h"

class demo_qt : public QMainWindow {
    Q_OBJECT

   public:
    demo_qt(QWidget* parent = nullptr);
    ~demo_qt();
    void draw_vertical_bar_chart();

   private:
    Ui_demo_qt* ui;

    QBarSet* set0;
    QBarSet* set1;
    QBarSet* set2;
    QBarSet* set3;
    QBarSet* set4;
    QBarSeries* series;
    QChart* chart;
    QBarCategoryAxis* axisX;
    QValueAxis* axisY;
    QChartView* chartView;
};