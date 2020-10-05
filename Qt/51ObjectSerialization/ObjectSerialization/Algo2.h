#ifndef ALGO2_H
#define ALGO2_H

#include <QObject>
#include <QDataStream>
#include "IAlgo.h"

class Algo2 : public IAlgo
{
    Q_OBJECT
    Q_PROPERTY(int width READ getWidth WRITE setWidth)
    Q_PROPERTY(int height READ getHeight WRITE setHeight)
    Q_PROPERTY(bool shared READ getShared WRITE setShared)
    Q_PROPERTY(float pi READ getPi WRITE setPi)

public:
    Q_INVOKABLE Algo2();
    ~Algo2();

    virtual void run() override;

    int getWidth() const;
    void setWidth(int value);

    int getHeight() const;
    void setHeight(int value);

    bool getShared() const;
    void setShared(bool value);

    float getPi() const;
    void setPi(float value);

private:
    int width;
    int height;
    bool shared;
    float pi;
};

#endif // ALGO2_H
