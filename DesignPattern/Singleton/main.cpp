#include <QCoreApplication>
#include <iostream>
#include "singleton.h"

class Keyboard
{
public:
    Keyboard(int a = 0, float b = 0.0)
    {
        std::cout << "Keyboard():" << (a+b) << std::endl;
    }

    ~Keyboard()
    {
        std::cout << "~Keyboard()" << std::endl;
    }

    void writeWords()
    {
        std::cout << "I'm writing! addr : " << (int)this << std::endl;
    }
};

int main(int argc, char *argv[])
{
    Keyboard* t1 = Singleton<Keyboard>::instance(5, 2.0);
    Keyboard* t2 = Singleton<Keyboard>::instance(6, 5.0);
    t1->writeWords();
    t2->writeWords();

    Singleton<Keyboard>::destroy();

    QCoreApplication a(argc, argv);

    return a.exec();
}
