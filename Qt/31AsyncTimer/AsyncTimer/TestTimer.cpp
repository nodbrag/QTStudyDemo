#include "TestTimer.h"
#include <QDebug>

TestTimer::TestTimer(QObject *parent)
    :AsyncTimer(1000, parent)
{

}

TestTimer::~TestTimer()
{
    // 注意：若在此类run()中使用了成员变量，则在此类对象析构前，
    // 必须调用waitForQuit()让线程先退出，否则可能出现此类成员变量已被析构，
    // 但是线程仍然还在运行run()的情况，此时访问成员变量出现段错误。
    // 建议：默认在子类析构函数中调用waitForQuit()。
    waitForQuit();
}

void TestTimer::run()
{
    // to do ...
    qDebug() << "do task in thread : " << QThread::currentThreadId();
    QThread::msleep(1000);  // 模拟do somthing

    emit statusChanged(55);  // 处理完毕，返回结果
}
