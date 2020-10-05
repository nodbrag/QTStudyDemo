#ifndef TESTOBJECT_H
#define TESTOBJECT_H

#include <QObject>
#include <QDebug>
#include "Person.h"
#include "MyObject.h"

class TestObject : public QObject
{
    Q_OBJECT
public:
    TestObject(QObject *parent = nullptr)
        : QObject(parent)
    {}

public slots:
    void ageFunc(int value) { qDebug() << "TestObject::ageFunc" << value; }
    void varFunc(int value) { qDebug() << "TestObject::varFunc" << value; }
    void scoreFunc(int value) { qDebug() << "TestObject::scoreFunc" << value; }
    void priorityFunc(MyObject::Priority pri) { qDebug() << "TestObject::priorityFunc" << pri; }
    void alignsFunc(MyObject::Aligns aligns) { qDebug() << "TestObject::alignsFunc" << aligns; }
    void personFunc(Person person)
    {
        qDebug() << "TestObject::personFunc" << person.varA << person.varB << person.varC;
    }
};

#endif // TESTOBJECT_H
