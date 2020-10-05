#include "HelloPlugin.h"
#include <QDebug>

HelloPlugin::HelloPlugin(QObject *parent)
    : HelloInterface(parent)
{
}

void HelloPlugin::func()
{
    emit dataChanged("i'am hello plugin!");
}

void HelloPlugin::setData(const QString &data)
{
    qDebug() << "HelloPlugin received : " << data;
}
