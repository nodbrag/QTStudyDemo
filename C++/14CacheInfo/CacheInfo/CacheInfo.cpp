#include "CacheInfo.h"
#include <assert.h>

CacheInfo::CacheInfo()
{
    instructionCache = new CacheLevelInfo[3];
    dataCache = new CacheLevelInfo[3];
    cacheInformation = new CacheLevelInfo*[2];
    cacheInformation[INSTRUCTION_CACHE] = instructionCache;
    cacheInformation[DATA_CACHE] = dataCache;
}

CacheInfo::~CacheInfo()
{
    delete [] cacheInformation;
    cacheInformation = nullptr;
    delete [] dataCache;
    dataCache = nullptr;
    delete [] instructionCache;
    instructionCache = nullptr;
}

bool CacheInfo::hasCache(CacheLevel level, CacheType type)
{
    assert(type != UNKNOWN_CACHE);
    return cacheInformation[type][level].getType() != UNKNOWN_CACHE;
}

CacheLevelInfo CacheInfo::getCacheInformation(CacheLevel level, CacheType type)
{
    assert(type != UNKNOWN_CACHE);
    return cacheInformation[type][level];
}

int CacheInfo::getCacheSize(CacheLevel level, CacheType type)
{
    assert(type != UNKNOWN_CACHE);
    return cacheInformation[type][level].getSize();
}

int CacheInfo::getCacheLineSize(CacheLevel level, CacheType type)
{
    assert(type != UNKNOWN_CACHE);
    return cacheInformation[type][level].getLineSize();
}

void CacheInfo::addCache(CacheLevelInfo cacheLevelInfo)
{
    if (cacheLevelInfo.getType() == INSTRUCTION_CACHE)
    {
        instructionCache[cacheLevelInfo.getLevel()] = cacheLevelInfo;
    }
    else if (cacheLevelInfo.getType() == DATA_CACHE)
    {
        dataCache[cacheLevelInfo.getLevel()] = cacheLevelInfo;
    }
}

void CacheInfo::clearCache()
{
    CacheLevelInfo invalidInfo;
    for (int i = 0; i < 3; i++)
    {
        instructionCache[i] = invalidInfo;
        dataCache[i] = invalidInfo;
    }
}
