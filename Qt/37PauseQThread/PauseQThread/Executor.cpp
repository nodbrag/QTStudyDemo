#include "Executor.h"
#include <QTimer>
#include <QEventLoop>

Executor::Executor(QObject *parent)
    : Thread(parent),
      startupDelay(0),
      intervalDelay(0)
{

}

Executor::~Executor()
{
    Thread::stop();
}

/**
 * @brief Executor::addRunable
 * 添加可执行对象，此处不加锁保护。
 * 建议：一次性添加完毕后，再启动线程。
 * @param able 可执行对象指针
 */
void Executor::addRunable(IRunable *able)
{
    runableList.append(able);
}

/**
 * @brief Executor::addRunables
 * 添加多个可执行对象，此处不加锁保护。
 * 建议：一次性添加完毕后，再启动线程。
 * @param ables 可执行对象指针列表
 */
void Executor::addRunables(const QList<IRunable *> &ables)
{
    runableList.append(ables);
}

/**
 * @brief Executor::getRunables
 * 获取所有可执行对象，多线程读，故此函数线程安全
 * @return 可执行对象指针列表
 */
QList<IRunable *> Executor::getRunables()
{
    return runableList;
}

/**
 * @brief Executor::setStartupDelay
 * 设置线程启动延迟时间（毫秒）
 * 建议：先设置，后启动线程，防止多线程竞争问题
 * @param ms 延迟时间
 */
void Executor::setStartupDelay(int ms)
{
    startupDelay = ms;
}

/**
 * @brief Executor::setIntervalDelay
 * 设置执行一遍所有对象后，休眠的时间（毫秒）
 * 建议：先设置，后启动线程，防止多线程竞争问题
 * @param ms 休眠时间
 */
void Executor::setIntervalDelay(int ms)
{
    intervalDelay = ms;
}

/**
 * @brief Executor::start
 * 重新包装基类启动方法，实现延迟启动
 * @param pri 优先级
 */
void Executor::start(QThread::Priority pri)
{
    if (startupDelay != 0)
    {
        QTimer::singleShot(startupDelay, this, [=]
        {
            Thread::start(pri);
        });
    }
    else
    {
        Thread::start(pri);
    }
}

/**
 * @brief Executor::process
 * 遍历执行对象
 */
void Executor::process()
{
    // 执行算法
    foreach (auto able, runableList)
    {
        able->exec();
    }

    if (intervalDelay != 0)
    {
        QTimer::singleShot(intervalDelay, this, [=]
        {
            Thread::resume();
        });
        Thread::pause();
    }
}
