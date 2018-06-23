#include "mainweight.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWeight weight;
    weight.show();

    return a.exec();
}
