/*
 * 说明：窗口部件拖拽对象演示程序；
*/

#include "DragDropDemo.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DragDropDemo w;
    w.show();

    return a.exec();
}
