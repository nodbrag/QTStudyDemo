#ifndef CPUUSAGEWIN_H
#define CPUUSAGEWIN_H

#include <windows.h>
#include <stdio.h>
#include <vector>
#include "ICpuUsage.h"

#define	SystemBasicInformation	0
#define	SystemPerformanceInformation	2
#define	SystemTimeInformation	3
#define SystemProcessorPerformanceInformation	8

typedef   LONG   (WINAPI   *PROCNTQSI)(UINT,PVOID,ULONG,PULONG);

typedef	struct SYSTEM_BASIC
{
    DWORD	dwUnknown1;
    ULONG	uKeMaximumIncrement;
    ULONG	uPageSize;
    ULONG	uMmNumberOfPhysicalPages;
    ULONG	uMmLowestPhysicalPage;
    ULONG   uMmHighestPhysicalPage;
    ULONG   uAllocationGranularity;
    PVOID   pLowestUserAddress;
    PVOID   pMmHighestUserAddress;
    ULONG   uKeActiveProcessors;
    BYTE	bKeNumberProcessors;
    BYTE    bUnknown2;
    WORD    wUnknown3;
}SYSTEM_BASIC_INFORMATION;

typedef struct SYSTEM_PROCESSOR_PERFORMANCE
{
    __int64 i64IdleTime;
    __int64 i64KernelTime;
    __int64 i64UserTime;
    __int64 i64DpcTime;
    __int64 i64InterruptTime;
    long lInterruptCount;
} SYSTEM_PROCESSOR_PERFORMANCE_INFORMATION;


class CpuUsageWin : public ICpuUsage
{
public:
    CpuUsageWin();
    virtual ~CpuUsageWin();
    virtual int init();
    virtual int getNumberProcessors();
    virtual int getUseage(const size_t);
    virtual void calProcessorsUses();
    virtual float getTemperature(int socketNo);
    virtual int    getSocketCount();

private:
    SYSTEM_PROCESSOR_PERFORMANCE_INFORMATION *processInfo;

    //save cpu percent of each processor
    int * cpuPercent;
    int processorCount;

    //save the old time of each processor
    __int64 * oldIdleTime;
    __int64 * oldKerenelTime;
    __int64 * oldUserTime;
    __int64 * oldDpctTime;
    __int64 * oldInterruptTime;
};

#endif // CPUUSAGEWIN_H
