#include <QCoreApplication>
#include "Thread1.h"
#include "Thread2.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

//    Thread1 th1;
//    th1.start();

    Thread2 th2;
    th2.start();

    return a.exec();
}
