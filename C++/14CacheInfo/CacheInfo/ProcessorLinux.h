#ifndef PROCESSORLINUX_H
#define PROCESSORLINUX_H

#include "CacheInfo.h"

class ProcessorLinux
{
public:
    static ProcessorLinux& getInstance()
    {
        static ProcessorLinux processor;
        return processor;
    }

    CacheInfo getCacheInfo();
    void refresh();

private:
    ProcessorLinux();
};

#endif // PROCESSORLINUX_H
