#include "demo_qt.h"

demo_qt::demo_qt(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui_demo_qt)
{
    ui->setupUi(this);
}

demo_qt::~demo_qt()
{
    delete ui;
}

void demo_qt::paintEvent(QPaintEvent* event) {
    QPainter *painter=new QPainter(this);
    // painter->drawLine(0,104,300,104);
    // painter->setRenderHint(QPainter::Antialiasing,true);
    // painter->drawArc(30,30,100,100,30*16,300*16);
    // painter->drawPie(350,350,100,100,0,360*16);
    // painter->drawRect(200,200,100,100);
    // painter->fillRect(400,100,100,100,QBrush{QColor{255,0,0,100}});
    painter->drawLine(50,300,350,300);
    painter->drawText(180,320,"Marcille meme emotion");
    delete painter;
}
