#include "Test3.h"
#include <QDebug>
#include "SysInfo.h"

void Test3::doSomething()
{
    SysInfo info;
    QString str = "on " + info.getSystemName() + ", doSomething!";
    qDebug() << str;
}
