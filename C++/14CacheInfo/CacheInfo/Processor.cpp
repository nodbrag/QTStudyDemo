#include "Processor.h"
#ifdef WIN32
#include "ProcessorWin.h"
#else
#include "ProcessorLinux.h"
#endif

#ifdef WIN32
    #define ProcessorInstance       ProcessorWin::getInstance()
#else
    #define ProcessorInstance       ProcessorLinux::getInstance()
#endif

CacheInfo Processor::getCacheInfo()
{
    return ProcessorInstance.getCacheInfo();
}

void Processor::refresh()
{
    ProcessorInstance.refresh();
}
