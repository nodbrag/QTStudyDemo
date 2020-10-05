#include <QCoreApplication>
#include "Reflect.h"
#include "print.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Reflect::registerClass<Print>();
    Base* object = (Base*)Reflect::newInstance("Print");
    object->setProperty("num", 55);
    object->setProperty("wid", 33);

    object->func();

    return a.exec();
}
