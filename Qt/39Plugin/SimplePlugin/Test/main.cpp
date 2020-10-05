#include <QCoreApplication>
#include <QtPlugin>
#include <QPluginLoader>
#include "HelloInterface.h"
#include "Test.h"

#define PLUGIN_FILE "./plugins/HelloPlugin.dll"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QPluginLoader loader(PLUGIN_FILE);
    QObject *obj = loader.instance();
    qDebug() << "class name : " << obj->metaObject()->className();
    HelloInterface *plugin = dynamic_cast<HelloInterface*>(obj);

    Test test;
    QObject::connect(plugin, SIGNAL(dataChanged(const QString&)),
                     &test, SLOT(recvFunc(const QString&)));
    QObject::connect(&test, SIGNAL(sendFunc(const QString&)),
                     plugin, SLOT(setData(const QString&)));

    plugin->func(); // plugin send signal
    emit test.sendFunc("test");  // plugin recv signal

    return a.exec();
}
