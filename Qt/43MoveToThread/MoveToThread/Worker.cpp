#include "Worker.h"
#include <QThread>
#include <QDebug>

Worker::Worker(QObject *parent)
    : QObject(parent)
{
    qDebug() << "Worker()" << "thread:" << QThread::currentThreadId();
}

Worker::~Worker()
{
    qDebug() << "~Worker()" << "thread:" << QThread::currentThreadId();
}

void Worker::doSomething(const QString &cmd)
{
    qDebug() << "doSomething()" << cmd << "thread:" << QThread::currentThreadId();
    emit resultNotify("doSomething ok!");
}
