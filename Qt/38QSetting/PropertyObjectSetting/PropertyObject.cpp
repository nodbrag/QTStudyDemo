#include "PropertyObject.h"

#define EQUAL_SYMBOL           "="
#define SEPARATOR_SYMBOL       ";"
#define END_SYMBOL             "$"

PropertyObject::RegisterType PropertyObject::autoRegType;

/**
 * @brief PropertyObject::PropertyObject
 * @param parent 父节点
 */
PropertyObject::PropertyObject(QObject *parent)
    : QObject(parent)
{

}

/**
 * @brief PropertyObject::PropertyObject
 * 拷贝构造函数：
 * 因为在保存此对象时，需要放入QVariant进行装箱，期间会有对象拷贝操作，
 * 然而QObject并没有拷贝构造函数，故我们继承于QObject，然后重写拷贝构造函数，
 * 完成obj对象中property的拷贝。
 * @param obj 被拷贝对象
 */
PropertyObject::PropertyObject(const PropertyObject &obj)
{
    copyProperties(this, &obj);
}

/**
 * @brief PropertyObject::operator =
 * 重载等号操作符
 * @param obj 等号右值
 * @return 等号左值引用，即当前对象引用
 */
PropertyObject &PropertyObject::operator=(const PropertyObject &obj)
{
    copyProperties(this, &obj);
    return *this;
}

/**
 * @brief PropertyObject::copyProperties
 * 拷贝属性列表
 * @param dst 目的对象
 * @param src 源对象
 */
void PropertyObject::copyProperties(QObject *dst, const QObject *src)
{
    QList<QByteArray> names = src->dynamicPropertyNames();
    for (int i = 0; i < names.size(); i++)
    {
        const char* name = names.at(i).data();
        QVariant value = src->property(name);
        dst->setProperty(name, value);
    }
}

/**
 * @brief operator <<
 * 重载插入操作符，将属性对象序列化
 * @param out 输出流
 * @param info 属性对象
 * @return 输出流引用
 */
QDataStream& operator<<(QDataStream &out, const PropertyObject& info)
{
    QList<QByteArray> properties = info.dynamicPropertyNames();
    for (int i = 0; i < properties.size(); i++)
    {
        const char* name = properties.at(i).data();
        QVariant value = info.property(name);

        out << QString(name) << QString(EQUAL_SYMBOL) << value; // 注意写入类型必须与读取类型一致
        if (i != properties.size() - 1)
        {
            out << QString(SEPARATOR_SYMBOL);
        }
        else
        {
            out << QString(END_SYMBOL);
        }
    }
    return out;
}

/**
 * @brief operator >>
 * 重载读取操作符，将输入流反序列化为属性对象
 * @param in 输入流
 * @param info 属性对象
 * @return 输入流引用
 */
QDataStream& operator>>(QDataStream &in, PropertyObject& info)
{
    QString separator;
    do //注意写入类型必须与读取类型一致
    {
        QString name;
        in >> name;

        QString equal;
        in >> equal;
        if (equal != QString(EQUAL_SYMBOL))
            break;

        QVariant value;
        in >> value;

        info.setProperty(name.toStdString().c_str(), value);

        separator.clear();
        in >> separator;
    } while (separator == QString(SEPARATOR_SYMBOL));
    return in;
}

PropertyObject::RegisterType::RegisterType()
{
    qRegisterMetaType<PropertyObject>("PropertyObject");
    qRegisterMetaTypeStreamOperators<PropertyObject>("PropertyObject");
}
