#ifndef CAR_H
#define CAR_H

#include <QObject>
#include <QDebug>

class Car : public QObject
{
    Q_OBJECT
public:
    Q_INVOKABLE Car()
    {
        qDebug() << "Car()";
    }

    Q_INVOKABLE Car(int a, double b)
    {
        qDebug() << "Car():" << a << b;
    }

    void run()
    {
        qDebug() << "I'm running";
    }
};

#endif // CAR_H
