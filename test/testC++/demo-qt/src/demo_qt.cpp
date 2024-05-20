#include "demo_qt.h"

demo_qt::demo_qt(QWidget* parent) : QMainWindow(parent), ui(new Ui_demo_qt) {
    ui->setupUi(this);
}

demo_qt::~demo_qt() {
    delete ui;
}