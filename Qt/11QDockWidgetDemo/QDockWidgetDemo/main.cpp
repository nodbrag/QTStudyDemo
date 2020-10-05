/*
 * 说明：QDockWidget使用演示程序；
*/

#include "QDockWidgetDemo.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QDockWidgetDemo w;
    w.show();

    return a.exec();
}
