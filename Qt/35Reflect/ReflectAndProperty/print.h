#ifndef PRINT_H
#define PRINT_H
#include <QDebug>
#include "base.h"

class Print : public Base
{
    Q_OBJECT
    Q_PROPERTY(int num READ getNum WRITE setNum)
public:
    Print(QObject* parent=nullptr)
        : Base(parent)
    {
        qDebug() << "constructor...";
    }

    virtual void func() override
    {
        qDebug() << "num :" << _num;
        qDebug() << "wid :" << getWid();
    }

    int getNum() const { return _num; }
    void setNum(int num) { _num = num; }

private:
    int _num;
};

#endif // PRINT_H
