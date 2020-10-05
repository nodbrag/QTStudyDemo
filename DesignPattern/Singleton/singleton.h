#ifndef SINGLETON_H
#define SINGLETON_H
#include <mutex>

template <class T>
class Singleton
{
private:
    Singleton() = default;
    ~Singleton() = default;
    Singleton(const Singleton&)=delete;
    Singleton& operator=(const Singleton&)=delete;

public:
    template <typename... Args>
    static T* instance(Args&&... args)
    {
        std::call_once(_flag, [&](){
            _instance = new T(std::forward<Args>(args)...);
        });
        return _instance;
    }

    static void destroy()
    {
        if (_instance)
        {
            delete _instance;
            _instance = NULL;
        }
    }

private:
    static T* _instance;
    static std::once_flag _flag;
};

template <class T>
T* Singleton<T>::_instance = NULL;

template <class T>
std::once_flag Singleton<T>::_flag;

#endif // SINGLETON_H
