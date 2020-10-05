#ifndef PROCESSORWIN_H
#define PROCESSORWIN_H

#include <Windows.h>
#include "CacheInfo.h"

class ProcessorWin
{
public:
    static ProcessorWin& getInstance()
    {
        static ProcessorWin processor;
        return processor;
    }

    CacheInfo getCacheInfo();
    void refresh();

private:
    ProcessorWin();

    DWORD CountSetBits(ULONG_PTR bitMask);
    void init();

private:
    typedef BOOL (WINAPI *GetLogicalProcessorInfoFunc)( PSYSTEM_LOGICAL_PROCESSOR_INFORMATION, PDWORD);
    CacheInfo cacheInfo;
};

#endif // PROCESSORWIN_H
