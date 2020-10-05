#include <QCoreApplication>
#include "Reflect.h"
#include "print.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // 注册类型
    Reflect<QObject*, int, double>::registerClass<Print>();

    // 实例化
    QObject* obj = Reflect<QObject*, int, double>::newInstance("Print", nullptr, 5, 3.6);
    Print* object = static_cast<Print*>(obj);
    object->func();

    return a.exec();
}
