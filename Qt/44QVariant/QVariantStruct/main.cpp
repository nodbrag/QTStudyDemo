#include <QCoreApplication>
#include <QVariant>
#include <QDebug>

struct Student
{
    QString name;
    int age;

    operator QVariant() const
    {
        return QVariant::fromValue(*this);
    }

    Student() {}
    Student(const QVariant& variant)
    {
        *this = variant.value<Student>();
    }
};
Q_DECLARE_METATYPE(Student)

void setVariant(const QVariant& value)
{
    qDebug() << "setVariant";
}

void setStudent(const Student& stu)
{
    qDebug() << "setStudent" << stu.name << stu.age;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Student stu1;
    stu1.name = "hh";
    stu1.age = 10;

    // 自定义类型转QVariant，用法1
    QVariant variant;
    variant.setValue<Student>(stu1);
    setVariant(variant);

    // 自定义类型转QVariant，用法2
    setVariant(QVariant::fromValue(stu1));

    // 自定义类型转QVariant，用法3
    setVariant(stu1); // 需要在结构体添加operator QVariant() const函数

    // QVariant转自定义类型，用法1
    Student stu2;
    stu2 = variant.value<Student>();
    setStudent(stu2);

    // QVariant转自定义类型，用法2
    setStudent(variant); // 需要在结构体添加Student(const QVariant& variant)构造函数

    return a.exec();
}
