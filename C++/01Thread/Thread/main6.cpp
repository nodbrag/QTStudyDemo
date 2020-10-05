#include <iostream>
#include <thread>

using namespace std;

void func()
{
    cout<<"thread is running" <<endl;
}

int main(int argc, char *argv[])
{
    thread t1(func);
    t1.detach();
    return 0;
}

