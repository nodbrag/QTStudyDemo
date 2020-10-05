#ifndef PRINT_H
#define PRINT_H
#include <QObject>
#include <QDebug>

class Print : public QObject
{
    Q_OBJECT
public:
    Print(QObject* parent, int a, double b)
        :QObject(parent)
    {
        qDebug() << "constructor..." << a << b;
    }

    void func()
    {
        qDebug() << "func...";
    }
};

#endif // PRINT_H
