#ifndef TEST2_H
#define TEST2_H

#include "ISysInfo.h"

class Test2
{
public:
    Test2();
    ~Test2();

    void doSomething();

private:
    ISysInfo* sysInfo;
};

#endif // TEST2_H
