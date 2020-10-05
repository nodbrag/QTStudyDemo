#ifndef ALGO1_H
#define ALGO1_H

#include <QObject>
#include <QDataStream>
#include "IAlgo.h"

class Algo1 : public IAlgo
{
    Q_OBJECT
    Q_PROPERTY(int size READ getSize WRITE setSize)
    Q_PROPERTY(QString path READ getPath WRITE setPath)
    Q_PROPERTY(bool shared READ getShared WRITE setShared)

public:
    Q_INVOKABLE Algo1();
    ~Algo1();

    virtual void run() override;

    int getSize() const;
    void setSize(int value);

    QString getPath() const;
    void setPath(const QString &value);

    bool getShared() const;
    void setShared(bool value);

private:
    int size;
    QString path;
    bool shared;
};

#endif // ALGO1_H
