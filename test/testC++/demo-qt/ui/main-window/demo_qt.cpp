#include "demo_qt.h"

demo_qt::demo_qt(QWidget* parent) : QMainWindow(parent), ui(new Ui_demo_qt) {
    ui->setupUi(this);
    connect(ui->cancelButton,&QPushButton::clicked,this,&demo_qt::onCancelButtonClicked);
    socket=new QTcpSocket(this);
    connect(ui->connectButton,&QPushButton::clicked,this,&demo_qt::onConnectButtonClicked);
}

demo_qt::~demo_qt() {
    delete ui;
}

void demo_qt::onCancelButtonClicked(){
    this->close();
}

void demo_qt::onConnectButtonClicked(){
    QString ip=ui->serverAddressLineEdit->text();
    QString port=ui->serverPortLineEdit->text();
    socket->connectToHost(QHostAddress(ip),port.toUShort());
    connect(socket,&QTcpSocket::connected,[this]{
        QMessageBox::information(this,"连接提示","连接服务器成功");
    });
    connect(socket,&QTcpSocket::disconnected,[this]{
        QMessageBox::warning(this,"连接提示","连接异常，网络断开");
    });
}