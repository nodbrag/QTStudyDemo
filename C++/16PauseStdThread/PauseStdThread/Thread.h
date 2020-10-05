#ifndef THREAD_H
#define THREAD_H

#include <thread>
#include <atomic>
#include <mutex>
#include <condition_variable>

class Thread
{
public:
    Thread();
    virtual ~Thread();

    enum State
    {
        Stoped,     ///<停止状态，包括从未启动过和启动后被停止
        Running,    ///<运行状态
        Paused      ///<暂停状态
    };

    State state() const;

    void start();
    void stop();
    void pause();
    void resume();

protected:
    virtual void process() = 0;

private:
    void run();

private:
    std::thread* _thread;
    std::mutex _mutex;
    std::condition_variable _condition;
    std::atomic_bool _pauseFlag;   ///<暂停标识
    std::atomic_bool _stopFlag;   ///<停止标识
    State _state;
};

#endif // THREAD_H
