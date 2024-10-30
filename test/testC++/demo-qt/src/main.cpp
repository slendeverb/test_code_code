#include "header.h"

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);
    demo_qt w;
    w.show();
    return a.exec();
}