#ifndef QUICKWORK_H
#define QUICKWORK_H

#include <QObject>
#include <QEvent>

#include "quick.h"
#include <QSet>
#include <QList>
#include <QString>
#include <QArgument>

#include "quickconfig.h"

class LIBRARYSHARED_EXPORT QuickWork : public QObject
{
    Q_OBJECT
    QUICK_EVENT(QObject)
public:

    typedef enum {
        MainThread = 0,
        WorkThread,
        NewThread
    } MoveThreadType;

    explicit QuickWork(QObject *parent = nullptr);
    virtual ~QuickWork();
    void moveToThread(QThread *thread);

    void setRunFlag(int value);
    MoveThreadType getMoveType() const;

signals:
    void quit();

public slots:
    virtual void start(){}
protected:
    int runFlag_;
    //对象移动方式
    MoveThreadType moveType_;
};

#endif // QUICKWORK_H
