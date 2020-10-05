#ifndef ORDERWORK_H
#define ORDERWORK_H

#include "quickwork.h"
#include <QString>

class OrderWork : public QuickWork
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit OrderWork(QuickWork *parent = 0);

public slots:
    void event_cross_thread(const QString &value);
    void start();
};
QUICK_AUTO(OrderWork)
#endif // ORDERWORK_H
