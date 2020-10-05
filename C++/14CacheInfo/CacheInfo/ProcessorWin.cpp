#include "ProcessorWin.h"
#include <QDebug>

CacheInfo ProcessorWin::getCacheInfo()
{
    return cacheInfo;
}

void ProcessorWin::refresh()
{
    init();
}

ProcessorWin::ProcessorWin()
{
    init();
}

// Helper function to count set bits in the processor mask.
DWORD ProcessorWin::CountSetBits(ULONG_PTR bitMask)
{
    DWORD LSHIFT = sizeof(ULONG_PTR)*8 - 1;
    DWORD bitSetCount = 0;
    ULONG_PTR bitTest = (ULONG_PTR)1 << LSHIFT;
    DWORD i;

    for (i = 0; i <= LSHIFT; ++i)
    {
        bitSetCount += ((bitMask & bitTest)?1:0);
        bitTest/=2;
    }

    return bitSetCount;
}

void ProcessorWin::init()
{
    // 获取"GetLogicalProcessorInformation"函数地址
    GetLogicalProcessorInfoFunc GetLogicalProcessorInfo = (GetLogicalProcessorInfoFunc) GetProcAddress(GetModuleHandle(TEXT("kernel32")), "GetLogicalProcessorInformation");
    if (nullptr == GetLogicalProcessorInfo)
    {
        qDebug() << "GetLogicalProcessorInformation is not supported.";
        return;
    }

    // 获取信息结构体长度，以便申请内存
    DWORD returnLength = 0;
    PSYSTEM_LOGICAL_PROCESSOR_INFORMATION buffer = nullptr;
    DWORD rc = GetLogicalProcessorInfo(buffer, &returnLength);
    if (FALSE == rc)
    {
        if (GetLastError() == ERROR_INSUFFICIENT_BUFFER)
        {
            buffer = (PSYSTEM_LOGICAL_PROCESSOR_INFORMATION)malloc(returnLength);
        }
        else
        {
            qDebug() << "Error %d" << GetLastError();
            return;
        }
    }

    // 获取ProcessorInfo
    rc = GetLogicalProcessorInfo(buffer, &returnLength);
    if (FALSE == rc)
    {
        qDebug() << "Error %d" << GetLastError();
        return;
    }

    // 解析ProcessorInfo
    int l1DCacheSize;
    int l1DCacheLineSize;
    int l1DWays;

    int l1ICacheSize;
    int l1ICacheLineSize;
    int l1IWays;

    int l2CacheSize;
    int l2CacheLineSize;
    int l2Ways;

    int l3CacheSize;
    int l3CacheLineSize;
    int l3Ways;
    DWORD processorL1CacheCount = 0;
    DWORD processorL2CacheCount = 0;
    DWORD processorL3CacheCount = 0;
    DWORD processorPackageCount = 0;
    PCACHE_DESCRIPTOR Cache = nullptr;
    int blockCount = returnLength / sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION);
    for (int i = 0; i < blockCount; i++)
    {
        switch (buffer[i].Relationship)
        {
        case RelationNumaNode:
            // Non-NUMA systems report a single record of this type.
            //numaNodeCount++;
            break;

        case RelationProcessorCore:
            //physicsCoreCount++;
            // A hyperthreaded core supplies more than one logical processor.
            //logicCoreCount += CountSetBits(buffer[i].ProcessorMask);
            break;

        case RelationCache:
            // Cache data is in ptr->Cache, one CACHE_DESCRIPTOR structure for each cache.
            Cache = &(buffer[i].Cache);

            if (Cache->Level == 1) // L1 Cache
            {
                processorL1CacheCount++;
                if (Cache->Type == CacheData)
                {
                    l1DCacheSize = Cache->Size;
                    l1DCacheLineSize = Cache->LineSize;
                    l1DWays = Cache->Associativity;
                }
                else if (Cache->Type == CacheInstruction)
                {
                    l1ICacheSize = Cache->Size;
                    l1ICacheLineSize = Cache->LineSize;
                    l1IWays = Cache->Associativity;
                }
            }
            else if (Cache->Level == 2) // L2 Cache
            {
                processorL2CacheCount++;
                l2CacheSize = Cache->Size;
                l2CacheLineSize = Cache->LineSize;
                l2Ways = Cache->Associativity;
            }
            else if (Cache->Level == 3) // L3 Cache
            {
                processorL3CacheCount++;
                l3CacheSize = Cache->Size;
                l3CacheLineSize = Cache->LineSize;
                l3Ways = Cache->Associativity;
            }
            break;

        case RelationProcessorPackage:
            // Logical processors share a physical package.
            processorPackageCount++;
            break;

        default:
            qDebug() << "Error: Unsupported LOGICAL_PROCESSOR_RELATIONSHIP value.";
            break;
        }
    }

    free(buffer);

    CacheLevelInfo l1IInfo(L1, INSTRUCTION_CACHE, l1ICacheLineSize, l1ICacheSize, l1IWays);
    CacheLevelInfo l1Dinfo(L1, DATA_CACHE, l1DCacheLineSize, l1DCacheSize, l1DWays);
    CacheLevelInfo l2Info(L2, DATA_CACHE, l2CacheLineSize, l2CacheSize, l2Ways);
    CacheLevelInfo l3Info(L3, DATA_CACHE, l3CacheLineSize, l3CacheSize, l3Ways);
    cacheInfo.clearCache();
    cacheInfo.addCache(l1IInfo);
    cacheInfo.addCache(l1Dinfo);
    cacheInfo.addCache(l2Info);
    cacheInfo.addCache(l3Info);
}
