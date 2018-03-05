#include "mainwindow.h"
#include <QApplication>
#include <QDesktopWidget>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    GeometryCalcUI* gmt = new GeometryCalcUI;

    gmt->move(a.desktop()->screenGeometry().height() - 25, 5);

    gmt->show();

    return a.exec();
}
