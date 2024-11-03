#include "demo_qt.h"

demo_qt::demo_qt(QWidget* parent) : QMainWindow(parent), ui(new Ui_demo_qt) {
    ui->setupUi(this);
    connect(ui->newAction, &QAction::triggered, this, &newActionSlot);
    connect(ui->openAction, &QAction::triggered, this, &openActionSlot);
    connect(ui->saveAction, &QAction::triggered, this, &saveActionSlot);
}

demo_qt::~demo_qt() {
    delete ui;
}

void demo_qt::newActionSlot() {
    ui->textEdit->clear();
    this->setWindowTitle("新建文本文档.txt");
}

void demo_qt::openActionSlot() {
    QString fileName = QFileDialog::getOpenFileName(
        this, "选择一个文件", QCoreApplication::applicationDirPath() + "/../src", "*.cpp");
    if (fileName.isEmpty()) {
        // QMessageBox::warning(this, "警告","请选择一个文件");
        qDebug() << "请选择一个文件";
    } else {
        qDebug() << fileName;
        QFile file(fileName);
        file.open(QIODevice::ReadOnly | QIODevice::Text);
        QByteArray byteArr = file.readAll();
        ui->textEdit->setText(byteArr);
        file.close();
    }
}

void demo_qt::saveActionSlot() {
    QString fileName = QFileDialog::getSaveFileName(
        this, "选择一个文件", QCoreApplication::applicationDirPath() + "/../src");
    if (fileName.isEmpty()) {
        qDebug() << "请选择一个文件";
    } else {
        QFile file(fileName);
        file.open(QIODevice::WriteOnly | QIODevice::Text);
        QByteArray byteArr;
        byteArr.append(ui->textEdit->toPlainText());
        file.write(byteArr);
        file.close();
    }
}

void demo_qt::keyPressEvent(QKeyEvent* k) {
    if (k->modifiers() == Qt::ControlModifier && k->key() == Qt::Key_S) {
        saveActionSlot();
    }
}

void demo_qt::mousePressEvent(QMouseEvent* m) {
    QPoint p = m->pos();
    qDebug() << p;

    if (m->button() == Qt::LeftButton) {
        qDebug() << "左键被按下";
    } else if (m->button() == Qt::RightButton) {
        qDebug() << "邮件被按下";
    }
}