#include <iostream>
#include <thread>

using namespace std;
/*
void func1(int n)
{
    n++;
    cout << "n = " << n <<endl;
}

void func2(int &n)
{
    n++;
    cout << "n = " << n <<endl;
}

int main(int argc, char *argv[])
{
    int n = 0;

    thread t1(func1, n);
    t1.join();
    cout << "n = " << n <<endl;

    thread t2(func2, ref(n));
    t2.join();
    cout << "n = " << n <<endl;

    return 0;
}
*/
