#include <QCoreApplication>
#include <QVariant>
#include "MyObject.h"
#include "TestObject.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    MyObject myObj;
    TestObject testObj;

    QObject::connect(&myObj, &MyObject::ageChanged, &testObj, &TestObject::ageFunc);
    QObject::connect(&myObj, &MyObject::varChanged, &testObj, &TestObject::varFunc);
    QObject::connect(&myObj, &MyObject::scoreChanged, &testObj, &TestObject::scoreFunc);
    QObject::connect(&myObj, &MyObject::priorityChanged, &testObj, &TestObject::priorityFunc);
    QObject::connect(&myObj, &MyObject::alignsChanged, &testObj, &TestObject::alignsFunc);
    QObject::connect(&myObj, &MyObject::personChanged, &testObj, &TestObject::personFunc);

    // age
    myObj.setAge(10);
    myObj.setProperty("age", 20);
    int aa = myObj.property("age").toInt();

    // var
    myObj.setVar(30);
    myObj.setProperty("var", 40);

    // score
    myObj.setProperty("score", 50);
    aa = myObj.property("score").toInt();

    // priority
    myObj.setProperty("priority", "VeryHigh");
    QVariant temp = myObj.property("priority");
    MyObject::Priority pri = temp.value<MyObject::Priority>();

    // aligns
    myObj.setAligns(MyObject::Left|MyObject::Bottom);
    myObj.setProperty("aligns", "Left|Top");
    temp = myObj.property("aligns");
    MyObject::Aligns aligns = temp.value<MyObject::Aligns>();

    // person
    Person person;
    person.varA = 10;
    person.varB = 5.0;
    person.varC = "test";
    myObj.setProperty("person", QVariant::fromValue(person));
    temp = myObj.property("person");
    Person result = temp.value<Person>();

    return a.exec();
}
