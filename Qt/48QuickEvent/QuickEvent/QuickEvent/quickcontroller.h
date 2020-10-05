#ifndef QUICKCONTROLLER_H
#define QUICKCONTROLLER_H

#include <QObject>
#include <QMap>
#include <QPair>
#include <QThread>
#include "quickconfig.h"

class QuickWork;

class LIBRARYSHARED_EXPORT QuickController : public QObject
{
    Q_OBJECT
public:
    QuickController(QObject *parent = nullptr);

    ~QuickController();

    static void *NewInstance(const char *name);

    static void destory();

signals:
    void startwork();

private:
    static QMap<QThread*, QuickWork*> threads_;

    static QPair<QThread*, QSet<QuickWork*> > workthread_;

    static QSet<QuickWork*> works_;

    static bool destory_flag_;
};

#endif // QUICKCONTROLLER_H
