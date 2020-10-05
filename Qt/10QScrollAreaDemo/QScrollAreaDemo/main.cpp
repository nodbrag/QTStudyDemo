/*
 * 说明：QSrollArea使用演示程序；
 * 只要使用QSrollArea的setWidget函数设置子窗口，且子窗口大小比QSrollArea窗口大，则就可以显示滚动条；
*/

#include "QScrollAreaDemo.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QScrollAreaDemo w;
    w.show();

    return a.exec();
}
