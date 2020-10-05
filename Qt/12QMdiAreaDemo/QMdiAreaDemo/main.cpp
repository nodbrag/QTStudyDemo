/*
 * 说明：QMdiArea多文档使用演示程序；
*/

#include "QMdiAreaDemo.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QMdiAreaDemo w;
    w.show();

    return a.exec();
}
