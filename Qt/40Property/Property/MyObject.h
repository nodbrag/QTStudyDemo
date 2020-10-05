#ifndef MYOBJECT_H
#define MYOBJECT_H

#include <QObject>
#include "Person.h"

class MyObject : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int age READ getAge WRITE setAge NOTIFY ageChanged) // 测试不带MEMBER字段
    Q_PROPERTY(int score MEMBER _score NOTIFY scoreChanged) // 测试带MEMBER字段
    Q_PROPERTY(int var READ getVar WRITE setVar NOTIFY varChanged)
    Q_PROPERTY(Priority priority READ priority WRITE setPriority NOTIFY priorityChanged) // 测试自定义枚举(单值)
    Q_PROPERTY(Aligns aligns READ aligns WRITE setAligns NOTIFY alignsChanged) // 测试自定义枚举(多值)

    Q_PROPERTY(Person person MEMBER _person NOTIFY personChanged) // 测试自定义类型
//    Q_PROPERTY(Person person READ getPerson WRITE setPerson NOTIFY personChanged)

public:
    enum Priority { High, Low, VeryHigh, VeryLow };
    Q_ENUM(Priority)

    enum Align
    {
        Left = 0x01,
        Right = 0x02,
        HCenter = 0x04,
        Top = 0x08,
        Bottom = 0x10,
        VCenter = 0x20
    };
    Q_DECLARE_FLAGS(Aligns, Align)
    Q_FLAG(Aligns)

    MyObject(QObject *parent = nullptr)
        : QObject(parent),
          _age(0),
          _score(0)
    {}

    int getAge() const
    {
        return _age;
    }
    void setAge(int value)
    {
        _age = value;
        emit ageChanged(value);
    }

    int getVar() const
    {
        // ....
        return 50;
    }
    void setVar(int value)
    {
        // ....
        emit varChanged(value);
    }

    void setPriority(Priority priority)
    {
        _priority = priority;
        emit priorityChanged(priority);
    }
    Priority priority() const
    {
        return _priority;
    }

    void setAligns(Aligns aligns)
    {
        _aligns = aligns;
        emit alignsChanged(aligns);
    }
    Aligns aligns() const
    {
        return _aligns;
    }

//    Person getPerson() const
//    {
//        return _person;
//    }
//    void setPerson(const Person &person)
//    {
//        _person = person;
//        emit personChanged(person);
//    }

signals:
    void ageChanged(int value);
    void scoreChanged(int value);
    void varChanged(int value);
    void priorityChanged(Priority priority);
    void alignsChanged(Aligns align);
    void personChanged(Person person);

private:
    int _age;
    int _score;
    Priority _priority;
    Aligns _aligns;
    Person _person;
};
Q_DECLARE_OPERATORS_FOR_FLAGS(MyObject::Aligns)

#endif // MYOBJECT_H
