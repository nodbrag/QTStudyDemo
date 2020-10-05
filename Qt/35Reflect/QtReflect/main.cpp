#include <QCoreApplication>
#include "car.h"
#include "Reflect.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // 注册类型
    Reflect::registerClass<Car>();

    // 实例化Car，无参构造函数
    Car* car1 = static_cast<Car*>(Reflect::newInstance("Car"));
    car1->run();

    // 实例化Car，带参构造函数
    Car* car2 = static_cast<Car*>( Reflect::newInstance("Car", Q_ARG(int, 5), Q_ARG(double, 2.6)) );
    car2->run();

    return a.exec();
}
