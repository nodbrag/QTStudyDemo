/*
说明：此程序仿qq的消息提示窗口；托盘图标有消息时闪烁。
     可以查看消息等。
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
