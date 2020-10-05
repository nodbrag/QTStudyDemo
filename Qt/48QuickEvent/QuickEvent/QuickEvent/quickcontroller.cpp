#include "quickcontroller.h"
#include "quickwork.h"

QMap<QThread*, QuickWork*> QuickController::threads_;
QPair<QThread*, QSet<QuickWork*> > QuickController::workthread_;
QSet<QuickWork*> QuickController::works_;
bool QuickController::destory_flag_ = false;

QuickController::QuickController(QObject *parent) : QObject(parent)
{
    auto list = static_cast< QSet<QByteArray> *>(NewInstance(nullptr));

    auto workt = new QThread(this);

    workthread_.first = nullptr;

    QSet<QuickWork*> set;

    foreach(auto var, *list)
    {
        auto type = QMetaType::type(var + "*");
        auto meta = QMetaType::metaObjectForType(type);
        auto obj = meta->newInstance(Q_ARG(QuickWork*, nullptr));
        auto work = qobject_cast<QuickWork*>(obj);

        if(work == nullptr)
            continue;

        QThread *t = nullptr;

        switch (work->getMoveType()) {
        case QuickWork::NewThread:
            t = new QThread(this);
            work->moveToThread(t);
            threads_.insert(t, work);
            t->start();
            break;
        case QuickWork::WorkThread:
            set.insert(work);
            work->moveToThread(workt);
            break;
        case QuickWork::MainThread:
            connect(this, &QuickController::startwork, work, &QuickWork::start);
            works_.insert(work);
            break;
        }
    }

    if(!set.isEmpty())
    {
        workthread_.first = workt;
        workthread_.second = set;
        workt->start();
    } else
    {
        workt->deleteLater();
    }

    if(!works_.isEmpty())
        emit startwork();
}

QuickController::~QuickController()
{
    if(!destory_flag_)
        destory();
}

void *QuickController::NewInstance(const char *name)
{
    static QSet<QByteArray> list;

    if(name != nullptr)
        list.insert(name);

    return (void *)&list;
}

void QuickController::destory()
{
    auto it = threads_.begin();

    for(; it != threads_.end(); ++ it)
    {
        it.value()->setRunFlag(false);
        it.key()->exit();
        workthread_.first->wait(10);
    }

    foreach(auto var, workthread_.second)
    {
        var->setRunFlag(false);
    }

    if(workthread_.first != nullptr)
    {
        workthread_.first->exit();
        workthread_.first->wait(5);
    }


    foreach(auto var, works_)
    {
        var->setRunFlag(false);
        delete var;
    }

    destory_flag_ = true;
}
