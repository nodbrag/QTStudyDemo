#include <QCoreApplication>
#include <QDebug>
#include "CTimer.h"

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

    double elapsed;
    CTimer timer;
    timer.reset();  // 开始计时

    testLogic(1000); // 运行逻辑

    elapsed = timer.end();  // 结束计时
    qDebug() << "elapsed time:" << elapsed << "us";

    ///////////////////////////////////////////////////////////
    timer.reset();  // 开始计时

    testLogic(10000); // 运行逻辑

    elapsed = timer.end();  // 结束计时
    qDebug() << "elapsed time:" << elapsed << "us";

    return a.exec();
}
