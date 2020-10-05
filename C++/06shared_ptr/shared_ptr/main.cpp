#include <QCoreApplication>
#include <iostream>

using namespace std;

class Buffer
{
public:
    Buffer()
    {
        cout << "Buffer()" << endl;
    }

    ~Buffer()
    {
        cout << "~Buffer()" << endl;
    }

    void getPtr()
    {
        cout << "get buffer ptr" << endl;
    }
};

class User
{
public:
    void setBuffer(shared_ptr<Buffer> pBuf)
    {
        pBuffer = pBuf;
    }

    void useBuffer()
    {
        pBuffer->getPtr();
    }

private:
    shared_ptr<Buffer> pBuffer;
};

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    shared_ptr<Buffer> pSharedBuffer = make_shared<Buffer>();
    cout << "use count:" << pSharedBuffer.use_count() << endl;

    User* user1 = new User();
    user1->setBuffer(pSharedBuffer);
    cout << "use count:" << pSharedBuffer.use_count() << endl;
    user1->useBuffer();

    User* user2 = new User();
    user2->setBuffer(pSharedBuffer);
    cout << "use count:" << pSharedBuffer.use_count() << endl;
    user2->useBuffer();

    delete user1;
    cout << "use count:" << pSharedBuffer.use_count() << endl;

    delete user2;
    cout << "use count:" << pSharedBuffer.use_count() << endl;

    pSharedBuffer.reset();
    cout << "use count:" << pSharedBuffer.use_count() << endl;

    return a.exec();
}
