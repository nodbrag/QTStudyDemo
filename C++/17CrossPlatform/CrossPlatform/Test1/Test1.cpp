#include "Test1.h"
#include <QString>
#include <QDebug>

void Test1::doSomething()
{
#ifdef WIN32
    // ...
    QString str = "on Windows 10, doSomething!";
#else
    // ...
    QString str = "on Ubuntu 16.04, doSomething!";
#endif
    qDebug() << str;
}
