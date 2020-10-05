#include <QCoreApplication>
#include <QSettings>
#include <QDebug>

void test_QStringList(QSettings *setting);
void test_StructObject(QSettings *setting);
void test_NestedStructObject(QSettings *setting);
void test_StructObjectList(QSettings *setting);
void test_StructObjectTree(QSettings *setting);

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QSettings* setting = new QSettings(qApp->applicationDirPath() + "/setting.ini", QSettings::IniFormat);

    test_QStringList(setting);
    test_StructObject(setting);
    test_NestedStructObject(setting);
    test_StructObjectList(setting);
    test_StructObjectTree(setting);

    delete setting;
    return a.exec();
}

// 测试写入、读取QStringList
void test_QStringList(QSettings *setting)
{
    // 定义
    QStringList list;
    list << "zhangsan" << "lisi" << "wangxiaohua";

    // 写入
    setting->setValue("AppAttribute/QStringList", list);

    // 读取
    QStringList listResult = setting->value("AppAttribute/QStringList").toStringList();
    qDebug() << listResult;
    qDebug() << "-----------------------------------------------\n";
}

// 测试写入、读取结构体对象
void test_StructObject(QSettings *setting)
{
    // 定义结构体
    QMap<QString, QVariant> person;
    person["name"] = "zhangsan";
    person["age"] = 25;
    person["sex"] = "man";

    // 写入
    setting->setValue("AppAttribute/Person", person);

    // 读取
    QMap<QString, QVariant> result = setting->value("AppAttribute/Person").toMap();
    qDebug() << result;
    qDebug() << "-----------------------------------------------\n";
}

// 测试写入、读取结构体下面嵌套结构体
void test_NestedStructObject(QSettings *setting)
{
    // 定义嵌套结构体
    QMap<QString, QVariant> car;
    car["brand"] = "Audi";
    car["price"] = 20;

    QMap<QString, QVariant> person;
    person["name"] = "zhangsan";
    person["age"] = 25;
    person["sex"] = "man";
    person["car"] = car;

    // 写入
    setting->setValue("AppAttribute/PersonCar", person);

    // 读取
    QMap<QString, QVariant> result = setting->value("AppAttribute/PersonCar").toMap();
    qDebug() << result;
    qDebug() << "-----------------------------------------------\n";
}

// 测试写入、读取结构体对象列表
void test_StructObjectList(QSettings *setting)
{
    // 定义结构体列表
    QMap<QString, QVariant> person1;
    person1["name"] = "zhangsan";
    person1["age"] = 25;
    person1["sex"] = "man";

    QMap<QString, QVariant> person2;
    person2["name"] = "lisi";
    person2["age"] = 30;
    person2["sex"] = "woman";

    QList<QVariant> list;
    list << person1 << person2;

    // 写入
    setting->setValue("AppAttribute/Persons", list);

    // 读取
    QList<QVariant> result = setting->value("AppAttribute/Persons").toList();
    qDebug() << result;
    qDebug() << "-----------------------------------------------\n";
}

// 测试写入、读取结构体对象树
void test_StructObjectTree(QSettings *setting)
{
    // 定义结构体对象树
    QMap<QString, QVariant> car1_0;
    car1_0["brand"] = "Audi";
    car1_0["price"] = 20;

    QMap<QString, QVariant> car1_1;
    car1_1["brand"] = "bmw";
    car1_1["price"] = 30;

    QMap<QString, QVariant> person1;
    person1["name"] = "zhangsan";
    person1["age"] = 25;
    person1["sex"] = "man";

    QList<QVariant> cars_1;
    cars_1 << car1_0 << car1_1;
    person1["cars"] = cars_1;

    /////////////////////////////////////////
    QMap<QString, QVariant> car2_0;
    car2_0["brand"] = "VOLVO";
    car2_0["price"] = 32;

    QMap<QString, QVariant> car2_1;
    car2_1["brand"] = "Benz";
    car2_1["price"] = 40;

    QMap<QString, QVariant> person2;
    person2["name"] = "lisi";
    person2["age"] = 31;
    person2["sex"] = "woman";

    QList<QVariant> cars_2;
    cars_2 << car2_0 << car2_1;
    person2["cars"] = cars_2;

    QList<QVariant> persons;
    persons << person1 << person2;

    // 写入
    setting->setValue("AppAttribute/PersonTree", persons);

    // 读取
    QList<QVariant> personsResult = setting->value("AppAttribute/PersonTree").toList();
    qDebug() << personsResult;
    qDebug() << "-----------------------------------------------\n";
}
