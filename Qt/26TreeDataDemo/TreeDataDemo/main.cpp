/*
 * 说明：树形结构数据添加至QTreeWidget的方法：
 * 1.递归方式
 * 2.迭代方式
 * 适用于：向QTreeWidget中添加树形结构数据时，其深度不确定的情况下，可以使用上述2种方法。
 * 使用时，需要将数据整理成Node类的形式，这个测试demo中每个Node只有一个名称数据，可以根据实际情况扩展保存其他的数据。
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
