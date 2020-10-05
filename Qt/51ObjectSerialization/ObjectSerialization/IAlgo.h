#ifndef IALGO_H
#define IALGO_H

#include <QVariantMap>
#include <QMetaProperty>

class IAlgo : public QObject
{
    Q_OBJECT

public:
    IAlgo() {}

    QVariantMap getProperties()
    {
        QVariantMap properties;
        const QMetaObject *metaobject = metaObject();
        int count = metaobject->propertyCount();
        for (int i = 0; i < count; ++i)
        {
            QMetaProperty metaproperty = metaobject->property(i);
            const char *name = metaproperty.name();
            QVariant value = property(name);
            properties[name] = value;
        }
        return properties;
    }

    void setProperties(const QVariantMap &properties)
    {
        QStringList names = properties.keys();
        foreach (auto name, names)
        {
            QVariant value = properties.value(name);
            setProperty(name.toStdString().c_str(), value);
        }
    }

    virtual void run() = 0;
};

#endif // IALGO_H
