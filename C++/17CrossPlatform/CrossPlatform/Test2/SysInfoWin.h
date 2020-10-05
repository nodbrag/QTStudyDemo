#ifndef SYSINFOWIN_H
#define SYSINFOWIN_H

#ifdef WIN32

#include "ISysInfo.h"

class SysInfoWin : public ISysInfo
{
public:
    virtual QString getSystemName() override
    {
        return "Windows 10";
    }
};

#endif

#endif // SYSINFOWIN_H
