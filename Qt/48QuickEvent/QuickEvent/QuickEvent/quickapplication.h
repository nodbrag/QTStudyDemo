#ifndef QUICKAPPLICATION_H
#define QUICKAPPLICATION_H

#include <QApplication>
#include <QObject>
#include <QSet>
#include <QMap>
#include <QReadWriteLock>
#include <QByteArray>
#include <QVariant>
#include <QSharedPointer>
#include <QThread>

#if defined(Q_OS_LINUX)
    #include <cxxabi.h>
#endif

#include "quickevent.h"
#include "quickconfig.h"

class QuickWork;

class LIBRARYSHARED_EXPORT QuickApplication : public QApplication {
    Q_OBJECT
  public:
    QuickApplication(int &argc, char **argv);

    virtual ~QuickApplication();

    template<class T>
    static void getList(QList<QByteArray> &typeNames,
                        QList<QGenericArgument> &list, T &&t) {
#if defined(Q_OS_LINUX)
        char *type = abi::__cxa_demangle(typeid(t).name(), nullptr, nullptr, nullptr);
        typeNames << QByteArray(type);
        list << Q_ARG(T, t);
        free(type);
#elif defined(Q_OS_WIN)
        typeNames << QByteArray(typeid(t).name());
        list << Q_ARG(T, t);
#endif
    }

    template<class T>
    static void getList(QList<QByteArray> &typeNames,
                        QList< QSharedPointer<QVariant> > &list, T &&t) {
#if defined(Q_OS_LINUX)
        char *type = abi::__cxa_demangle(typeid(t).name(), nullptr, nullptr, nullptr);
        typeNames << QByteArray(type);
        QSharedPointer<QVariant> ptr(new QVariant());
        ptr->setValue(t);
        list << ptr;
        free(type);
#elif defined(Q_OS_WIN)
        typeNames << QByteArray(typeid(t).name());
        QSharedPointer<QVariant> ptr(new QVariant());
        ptr->setValue(t);
        list << ptr;
#endif
    }

    template<class ...Args>
    static void publishEvent(QByteArray eventName, Qt::ConnectionType type, Args &&... args) {
        if(eventName.isEmpty()) {
            return ;
        }
        auto argsNum = sizeof...(args);
        Q_ASSERT_X(argsNum <= 10, "QuickEvent", "publishEvent argv number not greater than 10");
        QReadLocker loker(&s_lock);
        if(s_quick_event_pool.contains(eventName)) {
            auto set = s_quick_event_pool[eventName];
            auto methodName = QByteArray(METHODHEAD) + eventName;
            foreach (auto var, set) {
                //using qt support
                if(var->thread() == QThread::currentThread() ||
                        type == Qt::BlockingQueuedConnection) {
                    QList<QGenericArgument> list;
                    QList<QByteArray> typeNames;
                    std::initializer_list<int32_t> {(getList(typeNames, list, args), 0)...};
                    while(list.size() < 10) {
                        list << QGenericArgument();
                    }
                    auto index = -1;
                    if((index = methodIndex(var, typeNames, argsNum, methodName)) == -1) {
                        continue;
                    }
                    var->metaObject()->method(index).invoke(
                        var, type, list[0], list[1], list[2], list[3],
                        list[4], list[5], list[6], list[7], list[8], list[9]);
                } else { //quick event
                    QList< QSharedPointer<QVariant> > list;
                    QList<QByteArray> typeNames;
                    std::initializer_list<int32_t> {(getList(typeNames, list, args), 0)...};
                    QuickEvent *event = new QuickEvent();
                    event->setInfo(list);
                    event->setEventName(eventName);
                    QApplication::postEvent(var, event);
                }
            }
        }
    }

    static int methodIndex(QObject *recv, QList<QByteArray> &typeNames,
                           quint64 argsNum, QByteArray methodName);

    static bool subscibeEvent(QObject *listener, QByteArray eventName);

    static bool UnsubscribeEvent(QObject *listener, QByteArray eventName);

    static bool UnsubscribeEvent(QObject *listener);

    static void logoutEvent(QObject *listener, QByteArray eventName);

    static void exit(int rlt = 0);

  private:
    static QMap< QByteArray, QSet<QObject *> > s_quick_event_pool;

    static QReadWriteLock s_lock;
};

#endif // QUICKAPPLICATION_H
