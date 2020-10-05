#ifndef ISYSINFO_H
#define ISYSINFO_H

#include <QString>

class ISysInfo
{
public:
    virtual QString getSystemName() = 0;
};

#endif // ISYSINFO_H
