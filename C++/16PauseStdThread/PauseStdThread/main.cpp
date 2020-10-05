#include <QCoreApplication>
#include <iostream>
#include "Thread.h"

using namespace std;

void mySleep(int s)
{
    std::this_thread::sleep_for(std::chrono::duration<double>(s));
}

class MyThread : public Thread
{
protected:
    virtual void process() override
    {
        cout << "do my something" << endl;
        mySleep(1);
    }
};

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    MyThread thread;

    cout << "start thread" << endl;
    thread.start();
    cout << "thread state:" << thread.state() << endl;
    mySleep(3);

    cout << "pause thread" << endl;
    thread.pause();
    cout << "thread state:" << thread.state() << endl;
    mySleep(3);

    cout << "resume thread" << endl;
    thread.resume();
    cout << "thread state:" << thread.state() << endl;
    mySleep(3);

    cout << "stop thread" << endl;
    thread.stop();
    cout << "thread state:" << thread.state() << endl;
    mySleep(3);

    return a.exec();
}
