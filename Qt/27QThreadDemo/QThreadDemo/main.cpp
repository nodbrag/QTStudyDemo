/*
说明：演示QThread线程类的使用，以及证明当槽函数执行时间过长时，其他槽函数的执行被推迟现象。
*/

#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
