#include "quickevent.h"

QEvent::Type QuickEvent::S_QuickEvent = static_cast<QEvent::Type>(QEvent::registerEventType());


QuickEvent::QuickEvent(Type type):QEvent(type)
{
}

QuickEvent::QuickEvent(QByteArray eventName, QList<QSharedPointer<QVariant>> &info, QEvent::Type type)
    :QEvent(type), eventName_(eventName), info_(info)
{

}

QuickEvent::~QuickEvent()
{

}

QuickEvent &QuickEvent::operator=(const QuickEvent &other)
{
    eventName_ = other.eventName_;
    this->info_ = other.info_;
    return *this;
}

QByteArray QuickEvent::eventName() const
{
    return eventName_;
}

void QuickEvent::setEventName(const QByteArray &eventName)
{
    eventName_ = eventName;
}

void QuickEvent::setInfo(const QList<QSharedPointer<QVariant> > &info)
{
    info_ = info;
}

QList<QSharedPointer<QVariant> > QuickEvent::info() const
{
    return info_;
}
