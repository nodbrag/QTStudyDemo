#include <QCoreApplication>
#include <QDebug>
#include "TestTimer.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    qDebug() << "main thread : " << QThread::currentThreadId();

    TestTimer timer;
    TestTimer::connect(&timer, &TestTimer::statusChanged, [=] (int result) {
        qDebug() << "task result : " << result <<  " in thread : " << QThread::currentThreadId();
    });

    return a.exec();
}
