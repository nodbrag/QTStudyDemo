#ifndef THREAD1_H
#define THREAD1_H

#include <QThread>

class Thread1 : public QThread
{
    Q_OBJECT

protected:
    virtual void run() override;
};

#endif // THREAD1_H
