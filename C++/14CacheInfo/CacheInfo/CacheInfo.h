#ifndef CACHEINFO_H
#define CACHEINFO_H

#include "CacheLevelInfo.h"

#ifdef WIN32
class ProcessorWin;
#else
class ProcessorLinux;
#endif

class CacheInfo
{
public:
    CacheInfo();
    ~CacheInfo();

    bool hasCache(CacheLevel level, CacheType type);
    CacheLevelInfo getCacheInformation(CacheLevel level, CacheType type);
    int getCacheSize(CacheLevel level, CacheType type);
    int getCacheLineSize(CacheLevel level, CacheType type);

private:
#ifdef WIN32
    friend ProcessorWin;
#else
    friend ProcessorLinux;
#endif

    void addCache(CacheLevelInfo cacheLevelInfo);
    void clearCache();

private:
    CacheLevelInfo** cacheInformation;
    CacheLevelInfo* instructionCache;
    CacheLevelInfo* dataCache;
};

#endif // CACHEINFO_H
