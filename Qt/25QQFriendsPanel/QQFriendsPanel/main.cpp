#include "mainwindow.h"
#include <QApplication>


// 1.删除好友崩溃
// 2.不能允许分组名称相同
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.show();

    return a.exec();
}




