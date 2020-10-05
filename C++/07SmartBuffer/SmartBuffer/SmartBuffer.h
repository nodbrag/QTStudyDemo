#ifndef SMARTBUFFER_H
#define SMARTBUFFER_H

#include <utility>

/**
 * @brief The SmartBuffer class
 * 智能buffer类，此类既可作为共享buffer，也可作为私有buffer；
 * 将处理公私buffer的逻辑封装在其中。
 * 适用场景：比如某个算法可根据配置指定使用共享或私有buffer，那么在算法类中实例化此类，
 * 并传入shared参数，即可自动申请shared参数类型的一块buffer，并且在算法中使用时，无需关心
 * buffer到底是共享还是私有。
 * 内存管理：
 * 作为私有buffer时，内部buffer随SmartBuffer实例的释放被删除。
 * 作为共享buffer时，在最后一个SmartBuffer实例被释放时，内部buffer被删除。
 * VisitorT - 访问者类
 * BufferT - 此类将作为buffer类，在内部实例化
 */
template <class VisitorT, class BufferT>
class SmartBuffer
{
public:
    template <typename... Args>
    SmartBuffer(bool shared, Args&&... args)
        : privateObj(nullptr)
    {
        if (shared)
        {
            refCount++;
            if (sharedObj == nullptr) // 若共享，则仅在第一次实例化时创建BufferT
            {
                sharedObj = new BufferT(std::forward<Args>(args)...);
            }
        }
        else
        {
            privateObj = new BufferT(std::forward<Args>(args)...);
        }
    }

    ~SmartBuffer()
    {
        if (privateObj)
        {
            delete privateObj;
            privateObj = nullptr;
        }
        else
        {
            refCount--;
            if (sharedObj && refCount == 0) // 若共享，则仅在最后一次析构时释放BufferT
            {
                delete sharedObj;
                sharedObj = nullptr;
            }
        }
    }

    BufferT* buffer()
    {
        if (privateObj)
        {
            return privateObj;
        }
        else
        {
            return sharedObj;
        }
    }

private:
    SmartBuffer(const SmartBuffer&) = delete;
    SmartBuffer& operator=(const SmartBuffer&) = delete;

private:
    static int refCount;    ///<实例化引用计数，用于释放sharedObj
    static BufferT* sharedObj;  ///<每个VisitorT实例均共享sharedObj
    BufferT* privateObj;    ///<私有BufferT
};

template <class VisitorT, class BufferT>
int SmartBuffer<VisitorT, BufferT>::refCount = 0; ///<必须放在头文件，否则编译报错

template <class VisitorT, class BufferT>
BufferT* SmartBuffer<VisitorT, BufferT>::sharedObj = nullptr; ///<必须放在头文件，否则编译报错

#endif // SMARTBUFFER_H
