#include <QCoreApplication>
#include <QBuffer>
#include "IniConfig.h"
#include "Algo1.h"
#include "Algo2.h"
#include "Reflect.h"

void writeToConfigFile()
{
    Algo1 algo1;
    algo1.setSize(10);
    algo1.setPath("123");
    algo1.setShared(true);

    Algo2 algo2;
    algo2.setWidth(20);
    algo2.setHeight(30);
    algo2.setShared(false);
    algo2.setPi(3.14);

    QList<IAlgo*> list;
    list.append(&algo1);
    list.append(&algo2);

    IniConfig config;
    config.setAlgos(list);
}

void readFromConigFile()
{
    IniConfig config;
    QList<IAlgo *> list = config.getAlgos();

    foreach (auto algo, list)
    {
        algo->run();
    }

    qDeleteAll(list);
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // 注册类型
    Reflect::registerClass<Algo1>();
    Reflect::registerClass<Algo2>();

    writeToConfigFile();
    readFromConigFile();

    return a.exec();
}
