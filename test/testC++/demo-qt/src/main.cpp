#include "demo_qt.h"

#include <QApplication>
#pragma comment(lib, "user32.lib")

int main(int argc, char* argv[]) {
    std::cout << "Hello world\n";
    QApplication a(argc, argv);
    demo_qt w;
    w.show();
    qDebug()<<"QWidget .show\n";
    return a.exec();
}