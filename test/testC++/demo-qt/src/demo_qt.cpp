#include "demo_qt.h"

demo_qt::demo_qt(QWidget* parent) : QMainWindow(parent), ui(new Ui_demo_qt) {
    ui->setupUi(this);
    draw_vertical_bar_chart();
}

demo_qt::~demo_qt() {
    delete ui;

    delete chartView;
    delete axisX;
    delete axisY;
    delete chart;
    delete series;
    delete set0;
    delete set1;
    delete set2;
    delete set3;
    delete set4;
}

void demo_qt::draw_vertical_bar_chart() {
    set0 = new QBarSet{"Jane"};
    set1 = new QBarSet{"Jhon"};
    set2 = new QBarSet{"Axel"};
    set3 = new QBarSet{"Mary"};
    set4 = new QBarSet{"Samantha"};

    *set0 << 1 << 2 << 3 << 4 << 5 << 6;
    *set1 << 5 << 0 << 0 << 4 << 0 << 7;
    *set2 << 3 << 5 << 8 << 13 << 8 << 5;
    *set3 << 5 << 6 << 7 << 3 << 4 << 5;
    *set4 << 9 << 8 << 7 << 8 << 9 << 8;

    series = new QBarSeries{};
    series->append(set0);
    series->append(set1);
    series->append(set2);
    series->append(set3);
    series->append(set4);

    chart = new QChart{};
    chart->addSeries(series);
    chart->setTitle("Simple Barchart Example");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QStringList categories;
    categories << "Jan" << "Feb" << "Mar" << "Apr" << "May" << "Jun";
    axisX = new QBarCategoryAxis{};
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    axisY = new QValueAxis{};
    axisY->setTitleText("Values");
    axisY->setRange(0, 10);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    chartView = new QChartView{chart};
    chartView->setRenderHint(QPainter::Antialiasing);

    this->setCentralWidget(chartView);
    this->resize(800,600);
}
