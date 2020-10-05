#ifndef PROPERTYOBJECT_H
#define PROPERTYOBJECT_H

#include <QObject>
#include <QVariant>
#include <QDataStream>

/**
 * @brief The PropertyObject class
 * 通用属性对象
 */
class PropertyObject : public QObject
{
    Q_OBJECT
public:
    explicit PropertyObject(QObject *parent = nullptr);
    PropertyObject(const PropertyObject& obj);

    PropertyObject& operator=(const PropertyObject &obj);
    operator QVariant() const { return QVariant::fromValue(*this); }

    static void copyProperties(QObject *dst, const QObject *src);

private:
    class RegisterType
    {
    public:
        RegisterType();
    };
    static RegisterType autoRegType; ///< 实现自动注册PropertyObject类型
};
Q_DECLARE_METATYPE(PropertyObject)

QDataStream& operator<<(QDataStream &out, const PropertyObject& info);
QDataStream& operator>>(QDataStream &in, PropertyObject& info);

#endif // PROPERTYOBJECT_H
