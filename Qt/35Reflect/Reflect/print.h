#ifndef PRINT_H
#define PRINT_H
#include <QObject>
#include <QDebug>

class Print : public QObject
{
    Q_OBJECT
public:
    Print(QObject* parent=nullptr)
        :QObject(parent)
    {
        qDebug() << "constructor...";
    }

    void func()
    {
        qDebug() << "func...";
    }
};

#endif // PRINT_H
