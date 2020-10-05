#include "Worker.h"
#include <QDebug>

Worker::Worker(QObject *parent) :
    QObject(parent)
{
}

void Worker::do_work(const QString &para)
{
    qDebug() << "执行do_work()";
    int i = 0;
    while (i < 999999999)
    {
        i++;
    }

    emit signal_result(0);
}

void Worker::do_other()
{
    qDebug() << "执行do_other()";
    emit signal_other();
}
