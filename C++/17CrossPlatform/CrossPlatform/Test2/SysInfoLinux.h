#ifndef SYSINFOLINUX_H
#define SYSINFOLINUX_H

#ifdef __linux

#include "ISysInfo.h"

class SysInfoLinux : public ISysInfo
{
public:
    virtual QString getSystemName() override
    {
        return "Ubuntu 16.04";
    }
};

#endif

#endif // SYSINFOLINUX_H
