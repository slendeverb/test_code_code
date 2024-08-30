#include "demo_qt.h"

#include <QApplication>
#pragma comment(lib, "user32.lib")

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);
    demo_qt w;
    w.show();
    return a.exec();
}