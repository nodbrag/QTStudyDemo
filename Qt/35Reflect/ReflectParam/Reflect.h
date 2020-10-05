#ifndef REFLECT_H
#define REFLECT_H

#include <QByteArray>
#include <QMetaObject>
#include <QHash>

/**
 * @brief The Reflect class
 * 反射模板类，支持对变长构造函数参数类，的实例化
 */
template <typename... Args>
class Reflect
{
public:
    /**
     * @brief registerClass
     * 类注册函数
     */
    template<typename T>
    static void registerClass()
    {
        constructors().insert( T::staticMetaObject.className(), &constructorHelper<T> );
    }

    /**
     * @brief newInstance
     * 实例化对象函数
     * @param className 类名字符串
     * @param args 变长参数
     * @return 对象
     */
    //template <typename... Args>
    static QObject* newInstance( const QByteArray& className, Args... args )
    {
        Constructor constructor = constructors().value( className );
        if ( constructor == nullptr )
            return nullptr;
        return (*constructor)( std::forward<Args>(args)... );
    }

private:
    typedef QObject* (*Constructor)( Args... );

    template<typename T>
    static QObject* constructorHelper(Args... args )
    {
        return new T( std::forward<Args>(args)... );
    }

    static QHash<QByteArray, Constructor>& constructors()
    {
        static QHash<QByteArray, Constructor> instance;
        return instance;
    }
};

#endif // REFLECT_H
