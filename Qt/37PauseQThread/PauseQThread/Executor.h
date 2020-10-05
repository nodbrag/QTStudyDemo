#ifndef EXECUTOR_H
#define EXECUTOR_H
#include "Thread.h"
#include "IRunable.h"

/**
 * @brief The Executor class
 * 执行器类：
 * 进一步封装线程，添加执行对象接口，
 * 提供启动延迟与间隔延迟设置。
 */
class Executor : public Thread
{
public:
    Executor(QObject* parent = nullptr);
    ~Executor() override;

    void addRunable(IRunable* able);
    void addRunables(const QList<IRunable*>& ables);
    QList<IRunable*> getRunables();

    void setStartupDelay(int ms);
    void setIntervalDelay(int ms);

    void start(Priority pri = InheritPriority);

protected:
    virtual void process() override;

private:
    QList<IRunable*> runableList;   ///<执行对象列表
    int startupDelay;   ///<启动延迟时间ms
    int intervalDelay;  ///<间隔延迟时间ms
};

#endif // EXECUTOR_H
