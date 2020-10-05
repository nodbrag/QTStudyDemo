#ifndef ASYNCTIMER_H
#define ASYNCTIMER_H

#include <QThread>

class QTimer;

/**
 * @brief The AsyncTimer class
 * 异步定时器：
 * 创建一个新线程并在此线程上执行定时器,
 * 定时器周期性调用子类run()方法，执行在新线程上。
 */
class AsyncTimer : public QObject
{
    Q_OBJECT
public:
    AsyncTimer(int msec=1000, QObject* parent=nullptr);
    virtual ~AsyncTimer();

protected:
    void waitForQuit();

protected slots:
    virtual void run() = 0;

private:
    QThread thread;
    QTimer* timer;
};

#endif // ASYNCTIMER_H
