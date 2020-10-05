#include "Algo2.h"
#include <QDebug>

Algo2::Algo2()
    : width(0),
      height(0),
      shared(false),
      pi(0.0)
{

}

Algo2::~Algo2()
{

}

void Algo2::run()
{
    qDebug() << "Algo2::run()" << "width=" << width << ",height=" << height << ",shared=" << shared << ",pi=" << pi;
}

int Algo2::getWidth() const
{
    return width;
}

void Algo2::setWidth(int value)
{
    width = value;
}

int Algo2::getHeight() const
{
    return height;
}

void Algo2::setHeight(int value)
{
    height = value;
}

bool Algo2::getShared() const
{
    return shared;
}

void Algo2::setShared(bool value)
{
    shared = value;
}

float Algo2::getPi() const
{
    return pi;
}

void Algo2::setPi(float value)
{
    pi = value;
}
