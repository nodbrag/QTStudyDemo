#ifndef TESTTIMER_H
#define TESTTIMER_H

#include "AsyncTimer.h"

class TestTimer : public AsyncTimer
{
    Q_OBJECT
public:
    TestTimer(QObject* parent=nullptr);
    virtual ~TestTimer();

protected slots:
    virtual void run();

signals:
    void statusChanged(int result);
};

#endif // TESTTIMER_H
