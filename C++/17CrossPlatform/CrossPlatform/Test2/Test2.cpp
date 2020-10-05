#include "Test2.h"
#include <QDebug>
#ifdef WIN32
#include "SysInfoWin.h"
#else
#include "SysInfoLinux.h"
#endif

Test2::Test2()
{
#ifdef WIN32
    sysInfo = new SysInfoWin();
#else
    sysInfo = new SysInfoLinux();
#endif
}

Test2::~Test2()
{
    delete sysInfo;
    sysInfo = nullptr;
}

void Test2::doSomething()
{
    QString str = "on " + sysInfo->getSystemName() + ", doSomething!";
    qDebug() << str;
}
