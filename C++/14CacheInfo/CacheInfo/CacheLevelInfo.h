#ifndef CACHELEVELINFO_H
#define CACHELEVELINFO_H

enum CacheLevel
{
    L1,
    L2,
    L3
};

enum CacheType
{
    UNKNOWN_CACHE = -1,
    INSTRUCTION_CACHE,
    DATA_CACHE
};

class CacheLevelInfo
{
public:
    CacheLevelInfo();
    CacheLevelInfo(CacheLevel level, CacheType type, int lineSize, int size, int ways);

    CacheLevel getLevel() const;
    CacheType getType() const;
    int getLineSize() const;
    int getSize() const;
    int getWaysOfAssociativity() const;

private:
    CacheLevel level;
    CacheType type;
    int lineSize;
    int size;
    int waysOfAssociativity;
};

#endif // CACHELEVELINFO_H
