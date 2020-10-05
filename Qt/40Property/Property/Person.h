#ifndef PERSON_H
#define PERSON_H

#include <QVariant>

class Person
{
public:
    Person() { }

    bool operator!=(const Person& person)
    {
        if (person.varA == varA &&
            person.varB == varB &&
            person.varC == varC)
            return false;
        else
            return true;
    }

    int varA;
    float varB;
    QString varC;
};
Q_DECLARE_METATYPE(Person)

#endif // PERSON_H
