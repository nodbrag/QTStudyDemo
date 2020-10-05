#include "quickapplication.h"
#include "quickevent.h"
#include "quickwork.h"
#include "quickcontroller.h"

#include <QObject>
#include <QTimer>
#include <QEventLoop>

QMap< QByteArray, QSet<QObject *> > QuickApplication::s_quick_event_pool;
QReadWriteLock QuickApplication::s_lock;


QuickApplication::QuickApplication(int &argc, char **argv): QApplication(argc, argv) {
}

QuickApplication::~QuickApplication() {
}

void typeName(const QByteArray &s, QByteArray &d) {
    foreach (auto var, s) {
        if((var >= 'A' && var <= 'Z') ||
                (var >= 'a' && var <= 'z') ||
                (var >= '0' && var <= '9') ||
                var == '_') {
            d.append(var);
            continue;
        }
        break;
    }
}

bool checkpParameter(QList<QByteArray> s, QList<QByteArray> d) {
    for(int i = 0; i < d.size(); ++ i) {
        QByteArray name;
        typeName(d[i], name);
        if(name.isEmpty()) {
            return  false;
        }
        if(!(s[i].startsWith(name) || s[i].startsWith("class " + name))) {
            return false;
        }
    }
    return true;
}

int QuickApplication::methodIndex(QObject *recv, QList<QByteArray> &typeNames,
                                  quint64 argsNum, QByteArray methodName) {
    if(recv == nullptr) {
        return -1;
    }
    auto obj = recv->metaObject();
    for(int i = obj->methodOffset(); i < recv->metaObject()->methodCount(); ++ i) {
        auto method = obj->method(i);
        if(methodName == method.name()) {
            if(static_cast<unsigned int>(method.parameterCount()) > argsNum) {
                continue;
            }
            if(checkpParameter(typeNames, method.parameterTypes())) {
                return i;
            }
        }
    }
    return -1;
}

bool QuickApplication::subscibeEvent(QObject *listener, QByteArray eventName) {
    QWriteLocker loker(&s_lock);
    if(s_quick_event_pool.contains(eventName)) {
        QSet<QObject *> tmpset = s_quick_event_pool[eventName];
        tmpset.insert(listener);
        s_quick_event_pool.insert(eventName, tmpset);
        return true;
    }
    QSet<QObject *> tmpset;
    tmpset.insert(listener);
    s_quick_event_pool.insert(eventName, tmpset);
    return true;
}

bool QuickApplication::UnsubscribeEvent(QObject *listener, QByteArray eventName) {
    QWriteLocker loker(&s_lock);
    if(s_quick_event_pool.contains(eventName)) {
        QSet<QObject *> tmpset = s_quick_event_pool[eventName];
        tmpset.remove(listener);
        s_quick_event_pool.insert(eventName, tmpset);
        return true;
    }
    return false;
}

bool QuickApplication::UnsubscribeEvent(QObject *listener) {
    QWriteLocker loker(&s_lock);
    foreach (auto var, s_quick_event_pool.keys()) {
        s_quick_event_pool[var].remove(listener);
    }
    return true;
}

void QuickApplication::logoutEvent(QObject *listener, QByteArray eventName) {
    QWriteLocker loker(&s_lock);
    if(s_quick_event_pool.contains(eventName)) {
        QSet<QObject *> tmpset = s_quick_event_pool[eventName];
        tmpset.remove(listener);
        s_quick_event_pool.insert(eventName, tmpset);
    }
}

void QuickApplication::exit(int rlt) {
    QuickController::destory();
    qApp->exit(rlt);
}
