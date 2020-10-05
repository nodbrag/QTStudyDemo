#include <QCoreApplication>
#include "Reflect.h"
#include "print.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Reflect::registerClass<Print>();
    Print* object = (Print*)Reflect::newInstance("Print");
    object->func();

    return a.exec();
}
