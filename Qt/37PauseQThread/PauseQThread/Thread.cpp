#include "Thread.h"
#include <QDebug>

Thread::Thread(QObject *parent)
    : QThread(parent),
      pauseFlag(false),
      stopFlag(false)
{

}

Thread::~Thread()
{
    stop();
}

/**
 * @brief Thread::state
 * 获取线程状态
 * @return 状态
 */
Thread::State Thread::state() const
{
    State s = Stoped;
    if (!QThread::isRunning())
    {
        s = Stoped;
    }
    else if (QThread::isRunning() && pauseFlag)
    {
        s = Paused;
    }
    else if (QThread::isRunning() && (!pauseFlag))
    {
        s = Running;
    }
    return s;
}

/**
 * @brief Thread::start
 * 启动线程
 * @param pri 优先级
 */
void Thread::start(Priority pri)
{
    QThread::start(pri);
}

/**
 * @brief Thread::stop
 * 停止线程
 */
void Thread::stop()
{
    if (QThread::isRunning())
    {
        stopFlag = true;
        condition.wakeAll();
        QThread::quit();
        QThread::wait();
    }
}

/**
 * @brief Thread::pause
 * 暂停线程
 */
void Thread::pause()
{
    if (QThread::isRunning())
    {
        pauseFlag = true;
    }
}

/**
 * @brief Thread::resume
 * 继续线程
 */
void Thread::resume()
{
    if (QThread::isRunning())
    {
        pauseFlag = false;
        condition.wakeAll();
    }
}

/**
 * @brief Thread::run
 * 线程函数，此函数不允许被重写。
 * 子类应该重写process()。
 */
void Thread::run()
{
    qDebug() << "enter thread : " << QThread::currentThreadId();

    while (!stopFlag)
    {
        process();
        if (pauseFlag)
        {
            mutex.lock();
            condition.wait(&mutex);
            mutex.unlock();
        }
    }
    pauseFlag = false;
    stopFlag = false;

    qDebug() << "exit thread : " << QThread::currentThreadId();
}
