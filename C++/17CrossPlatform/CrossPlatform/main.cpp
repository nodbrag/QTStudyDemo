#include <QCoreApplication>
#include "Test1.h"
#include "Test2.h"
#include "Test3.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Test1 test1;
    test1.doSomething();

    Test2 test2;
    test2.doSomething();

    Test3 test3;
    test3.doSomething();

    return a.exec();
}
