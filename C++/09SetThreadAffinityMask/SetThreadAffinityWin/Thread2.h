#ifndef THREAD2_H
#define THREAD2_H

#include <QThread>

class Thread2 : public QThread
{
    Q_OBJECT

protected:
    virtual void run() override;
};

#endif // THREAD2_H
