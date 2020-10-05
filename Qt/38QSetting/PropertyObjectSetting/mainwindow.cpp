#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QVariant>
#include "ApplicationSetting.h"
#include "PropertyObject.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ApplicationSetting setting;

    testStructObject(&setting);
    qDebug() << "----------------------------------------------";

    testNestedStructObject(&setting);
    qDebug() << "----------------------------------------------";

    testStructObjectList(&setting);
    qDebug() << "----------------------------------------------";

    testStructObjectTree(&setting);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::print(QObject *object)
{
    QList<QByteArray> properties = object->dynamicPropertyNames();
    for (int i = 0; i < properties.size(); i++)
    {
        QString name = properties.at(i);

        QVariant value = object->property(properties.at(i).data());
        if (QString(value.typeName()) == "PropertyObject")
        {
            PropertyObject obj = value.value<PropertyObject>();
            QString str = QString("QVariant(PropertyObject, count = %1) :").arg(obj.dynamicPropertyNames().size());
            qDebug() << name << "=" << str;
            print(&obj);
        }
        else
        {
            qDebug() << name << "=" << value;
        }
    }
}

// 测试写入、读取结构体对象
void MainWindow::testStructObject(ApplicationSetting *setting)
{
    // 写入
    PropertyObject src;
    src.setProperty("string", "456");
    src.setProperty("int", 80);
    src.setProperty("float", 58.9);
    src.setProperty("bool", true);
    src.setProperty("QSize", QSize(20, 50));
    setting->setValue("AppAttribute/Struct", src);

    // 读取
    QVariant var = setting->value("AppAttribute/Struct");
    PropertyObject dst = var.value<PropertyObject>();
    print(&dst);
}

// 测试写入、读取结构体下面嵌套结构体
void MainWindow::testNestedStructObject(ApplicationSetting *setting)
{
    // 写入
    PropertyObject src;
    src.setProperty("string", "456");
    src.setProperty("int", 80);

    PropertyObject nested;
    nested.setProperty("int", 59);
    nested.setProperty("float", 25.3);
    src.setProperty("nested", nested);

    setting->setValue("AppAttribute/NestedStruct", src);

    // 读取
    QVariant var = setting->value("AppAttribute/NestedStruct");
    PropertyObject dst = var.value<PropertyObject>();
    print(&dst);
}

// 测试写入、读取结构体对象列表
void MainWindow::testStructObjectList(ApplicationSetting *setting)
{
    // 写入
    PropertyObject list;

    PropertyObject member0;
    member0.setProperty("int", 23);
    member0.setProperty("float", 29.3);
    list.setProperty("member0", member0);

    PropertyObject member1;
    member1.setProperty("int", 89);
    member1.setProperty("bool", true);
    list.setProperty("member1", member1);

    PropertyObject member2;
    member2.setProperty("string", "test");
    member2.setProperty("float", 2.3);
    list.setProperty("member2", member2);

    setting->setValue("AppAttribute/List", list);

    // 读取
    QVariant var = setting->value("AppAttribute/List");
    PropertyObject dst = var.value<PropertyObject>();
    print(&dst);
}

// 测试写入、读取结构体对象树
void MainWindow::testStructObjectTree(ApplicationSetting *setting)
{
    // 写入
    PropertyObject root;

    // item0
    PropertyObject item0;

    PropertyObject item0_0;
    item0_0.setProperty("int", 96);

    PropertyObject item0_1;
    item0_1.setProperty("int", 36);

    item0.setProperty("item0_0", item0_0);// item0添加节点0
    item0.setProperty("item0_1", item0_1);// item0添加节点1

    // item1
    PropertyObject item1;

    PropertyObject item1_0;
    item1_0.setProperty("int", 15);

    PropertyObject item1_1;
    item1_1.setProperty("int", 25);

    item1.setProperty("item1_0", item1_0);// item1添加节点0
    item1.setProperty("item1_1", item1_1);// item1添加节点1

    root.setProperty("item0", item0);// root添加节点item0
    root.setProperty("item1", item1);// root添加节点item1

    setting->setValue("AppAttribute/Tree", root);

    // 读取
    QVariant var = setting->value("AppAttribute/Tree");
    PropertyObject dst = var.value<PropertyObject>();
    print(&dst);
}
