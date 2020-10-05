#include "orderwork.h"
#include "quickapplication.h"
#include <QTimer>
#include <QEventLoop>
#include <QDebug>

OrderWork::OrderWork(QuickWork *parent) : QuickWork(parent)
{
    moveType_ = NewThread;
    QuickApplication::subscibeEvent(this, "cross_thread");
}

void OrderWork::event_cross_thread(const QString &value)
{
    qDebug() << "recv value :" << value << "thread id :" << QThread::currentThreadId();
}

void OrderWork::start()
{
    while(runFlag_)
    {
        qDebug() << "in OrderWork::start() circle," << "thread id :" << QThread::currentThreadId();

        QTimer timer;
        QEventLoop loop;

        connect(&timer, &QTimer::timeout, &loop, &QEventLoop::quit);
        connect(this, &QuickWork::quit, &loop, &QEventLoop::quit);

        timer.start(1000);
        loop.exec();
    }
}
