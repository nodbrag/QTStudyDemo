#include "Algo1.h"
#include <QDebug>

Algo1::Algo1()
    : size(0),
      shared(false)
{

}

Algo1::~Algo1()
{

}

void Algo1::run()
{
    qDebug() << "Algo1::run()" << "size=" << size << ",path=" << path << ",shared=" << shared;
}

int Algo1::getSize() const
{
    return size;
}

void Algo1::setSize(int value)
{
    size = value;
}

QString Algo1::getPath() const
{
    return path;
}

void Algo1::setPath(const QString &value)
{
    path = value;
}

bool Algo1::getShared() const
{
    return shared;
}

void Algo1::setShared(bool value)
{
    shared = value;
}
