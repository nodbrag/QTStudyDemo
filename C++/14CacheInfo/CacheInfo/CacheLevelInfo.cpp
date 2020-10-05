#include "CacheLevelInfo.h"

CacheLevelInfo::CacheLevelInfo()
    : level(L1),
      type(UNKNOWN_CACHE),
      lineSize(0),
      size(0),
      waysOfAssociativity(0)
{

}

CacheLevelInfo::CacheLevelInfo(CacheLevel level, CacheType type, int lineSize, int size, int ways)
    : level(level),
      type(type),
      lineSize(lineSize),
      size(size),
      waysOfAssociativity(ways)
{

}

CacheLevel CacheLevelInfo::getLevel() const
{
    return level;
}

CacheType CacheLevelInfo::getType() const
{
    return type;
}

int CacheLevelInfo::getLineSize() const
{
    return lineSize;
}

int CacheLevelInfo::getSize() const
{
    return size;
}

int CacheLevelInfo::getWaysOfAssociativity() const
{
    return waysOfAssociativity;
}
