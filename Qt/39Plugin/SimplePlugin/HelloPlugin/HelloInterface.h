#ifndef HELLOINTERFACE_H
#define HELLOINTERFACE_H

#include <QObject>

#define HelloPluginInterface_iid "org.qt-project.User.HelloInterface"

class HelloInterface : public QObject
{
    Q_OBJECT
public:
    HelloInterface(QObject* parent) :QObject(parent)  { }
    virtual void func() = 0;

public slots:
    virtual void setData(const QString& data) = 0;

signals:
    void dataChanged(const QString& str);
};

Q_DECLARE_INTERFACE(HelloInterface, HelloPluginInterface_iid)

#endif // HELLOINTERFACE_H
