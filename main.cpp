#include "clientdemo.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ClientDemo w;
    w.show();

    return a.exec();
}
