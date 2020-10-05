#include <QCoreApplication>
#include <iostream>
#include <QMutex>
#include "SmartBuffer.h"

class MemoryBlock
{
public:
    MemoryBlock(size_t size)
    {
        _ptr = new char[size];
        _size = size;
        std::cout << "alloc memory : " << this << std::endl;
    }

    ~MemoryBlock()
    {
        delete[] (char*)_ptr;
        _ptr = nullptr;
        std::cout << "free memory : " << this << std::endl;
    }

    void* ptr()
    {
        return _ptr;
    }

    size_t size()
    {
        return _size;
    }

    QMutex* mutex() { return &_mutex; }

private:
    void* _ptr;
    size_t _size;
    QMutex _mutex;  ///<可根据需要，在此类中保存一把锁，用于共享缓存，多线程竞争问题
};

class TestAlgo1
{
public:
    TestAlgo1(bool shared)
    {
        std::cout << "TestAlgo1()" << std::endl;
        buffer = new SmartBufferT(shared, 20);
    }

    virtual ~TestAlgo1()
    {
        std::cout << "~TestAlgo1()" << std::endl;
        delete buffer;
        buffer = nullptr;
    }

    // 假设此函数被多个线程调用
    virtual void run()
    {
        QMutex* mutex = buffer->buffer()->mutex();
        mutex->lock();

        // 读写操作buffer
        // void* ptr = buffer->buffer()->ptr();
        // size_t size = buffer->buffer()->size();

        mutex->unlock();
    }

private:
    typedef SmartBuffer<TestAlgo1, MemoryBlock> SmartBufferT;
    SmartBufferT* buffer;
};

class TestAlgo2
{
public:
    TestAlgo2(bool shared)
    {
        std::cout << "TestAlgo2()" << std::endl;
        buffer = new SmartBufferT(shared, 20);
    }

    virtual ~TestAlgo2()
    {
        std::cout << "~TestAlgo2()" << std::endl;
        delete buffer;
        buffer = nullptr;
    }

    // 假设此函数被多个线程调用
    virtual void run()
    {
        QMutex* mutex = buffer->buffer()->mutex();
        mutex->lock();

        // 读写操作buffer
        // void* ptr = buffer->buffer()->ptr();
        // size_t size = buffer->buffer()->size();

        mutex->unlock();
    }

private:
    typedef SmartBuffer<TestAlgo2, MemoryBlock> SmartBufferT;
    SmartBufferT* buffer;
};

class TestAlgo3
{
public:
    TestAlgo3(bool shared)
    {
        std::cout << "TestAlgo3()" << std::endl;
        buffer = new SmartBufferT(shared, 20);
    }

    virtual ~TestAlgo3()
    {
        std::cout << "~TestAlgo3()" << std::endl;
        delete buffer;
        buffer = nullptr;
    }

    // 假设此函数被多个线程调用
    virtual void run()
    {
        // 读写操作buffer
        // void* ptr = buffer->buffer()->ptr();
        // size_t size = buffer->buffer()->size();
    }

private:
    typedef SmartBuffer<TestAlgo3, MemoryBlock> SmartBufferT;
    SmartBufferT* buffer;
};

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    TestAlgo1* algo1_1 = new TestAlgo1(true);
    TestAlgo1* algo1_2 = new TestAlgo1(true);

    TestAlgo2* algo2_1 = new TestAlgo2(false);
    TestAlgo2* algo2_2 = new TestAlgo2(false);

    TestAlgo3* algo3_1 = new TestAlgo3(true);
    TestAlgo3* algo3_2 = new TestAlgo3(false);
    TestAlgo3* algo3_3 = new TestAlgo3(true);

    delete algo1_1;
    delete algo1_2;

    delete algo2_1;
    delete algo2_2;

    delete algo3_1;
    delete algo3_2;
    delete algo3_3;

    return a.exec();
}
