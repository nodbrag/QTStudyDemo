#include <QCoreApplication>
#include <iostream>
#include <QSharedData>
#include <QSharedDataPointer>

class EmployeeData : public QSharedData
{
public:
    EmployeeData()
        : id(-1)
    {
        std::cout << "EmployeeData()" << std::endl;
    }

    EmployeeData(const EmployeeData &other)
        : QSharedData(other),
          id(other.id),
          name(other.name)
    {
        std::cout << "EmployeeData(const EmployeeData &other)" << std::endl;
    }

    ~EmployeeData()
    {
        std::cout << "~EmployeeData()" << std::endl;
    }

    int id;
    QString name;
};

class Employee
{
public:
    Employee()
    {
        d = new EmployeeData;
        std::cout << "Employee()" << std::endl;
    }

    Employee(int id, QString name)
    {
        std::cout << "Employee(int id, QString name)()" << std::endl;
        d = new EmployeeData;
        setId(id);
        setName(name);
    }

    Employee(const Employee &other)
          : d(other.d)
    {
        std::cout << "Employee(const Employee &other)" << std::endl;
    }

    void setId(int id) { d->id = id; }
    void setName(QString name) { d->name = name; }

    bool operator==( const Employee & other ) const
    {
        std::cout << "Employee(operator==)" << std::endl;
        if(d ==other.d)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    int id() const { return d->id; }
    QString name() const { return d->name; }

private:
    QSharedDataPointer<EmployeeData> d;
};

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Employee e1(1001, "Albrecht Durer");
    Employee e2 = e1;

    e1.setName("HansHolbein");

    return a.exec();
}
