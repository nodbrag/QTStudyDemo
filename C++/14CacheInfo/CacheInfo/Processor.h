#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "CacheInfo.h"

class Processor
{
public:
    CacheInfo getCacheInfo();
    void refresh();
};

#endif // PROCESSOR_H
