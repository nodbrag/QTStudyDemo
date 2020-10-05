#include "IniConfig.h"
#include <QSettings>
#include <QCoreApplication>
#include <QDebug>
#include "Reflect.h"
#include "Algo1.h"
#include "Algo2.h"

IniConfig::IniConfig()
{
    setting = new QSettings(qApp->applicationDirPath() + "/setting.ini", QSettings::IniFormat);
}

IniConfig::~IniConfig()
{
    delete setting;
    setting = nullptr;
}

void IniConfig::setAlgos(const QList<IAlgo*>& algos)
{
    QVariantList algos_properties;
    foreach (auto algo, algos)
    {
        QVariantMap properties = algo->getProperties();

        const char *className = algo->metaObject()->className();
        properties["className"] = className;

        algos_properties.append(properties);
    }
    setting->setValue("app/algos", algos_properties);
}

QList<IAlgo *> IniConfig::getAlgos() const
{
    QList<IAlgo *> algos;
    QVariantList algos_properties = setting->value("app/algos").toList();
    foreach (auto properties, algos_properties)
    {
        QVariantMap map = properties.toMap();
        QByteArray className = map.value("className").toByteArray();
        IAlgo* algo = qobject_cast<IAlgo*>(Reflect::newInstance(className));
        if (algo == nullptr)
        {
            qDebug() << className << "class name is not registered!";
            continue;
        }

        map.remove("className");
        algo->setProperties(map);
        algos.append(algo);
    }
    return algos;
}
