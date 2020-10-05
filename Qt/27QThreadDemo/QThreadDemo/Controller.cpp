#include "Controller.h"
#include "Worker.h"
#include <QDebug>

Controller::Controller(QObject *parent) :
    QObject(parent)
{
    Worker* worker = new Worker();
    worker->moveToThread(&_thread);
    connect(&_thread, SIGNAL(finished()), worker, SLOT(deleteLater()));

    connect(this, SIGNAL(signal_operate(QString)), worker, SLOT(do_work(QString)));
    connect(worker, SIGNAL(signal_result(int)), this, SLOT(slot_handleResults(int)));

    connect(this, SIGNAL(signal_other()), worker, SLOT(do_other()));
    connect(worker, SIGNAL(signal_other()), this, SLOT(slot_handleOtherRes()));

    _thread.start();
}

Controller::~Controller()
{
    _thread.quit();
    _thread.wait();
}

void Controller::operate(const QString &para)
{
    emit signal_operate(para);
}

void Controller::other()
{
    emit signal_other();
}

void Controller::slot_handleResults(int code)
{
    qDebug() << "输出处理结果1";
}

void Controller::slot_handleOtherRes()
{
    qDebug() << "输出处理结果2";
}
