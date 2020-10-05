#include <QCoreApplication>
#include <QDebug>
#include "CTimer.h"
#include "CTimerNs.h"

void testLogic(int repeat)
{
    int sum = 0;
    for (int i = 0; i < repeat; i++)
    {
        sum += i;
    }
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    CTimer timer;
    timer.reset();  // 开始计时

    testLogic(1000); // 运行逻辑

    double elapsed = timer.end();  // 结束计时
    qDebug() << "elapsed time:" << elapsed << "us";

    ///////////////////////////////////////////////////////////
    CTimerNs timerNs;
    timerNs.reset();  // 开始计时

    testLogic(1000); // 运行逻辑

    long long elapsedNs = timerNs.end();  // 结束计时
    qDebug() << "elapsed time:" << elapsedNs << "ns";

    return a.exec();
}
