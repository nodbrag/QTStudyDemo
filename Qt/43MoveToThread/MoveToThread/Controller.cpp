#include "Controller.h"
#include <QDebug>
#include "Worker.h"

Controller::Controller(QObject* parent)
    : QObject(parent)
{
    Worker *worker = new Worker();
    worker->moveToThread(&thread);
    connect(&thread, &QThread::finished, worker, &QObject::deleteLater);
    connect(this, &Controller::operate, worker, &Worker::doSomething);
    connect(worker, &Worker::resultNotify, this, &Controller::handleResults);
    thread.start();
}

Controller::~Controller()
{
    thread.quit();
    thread.wait();
}

void Controller::handleResults(const QString &des)
{
    qDebug() << "handleResults()" << des << "thread:" << QThread::currentThreadId();
}
