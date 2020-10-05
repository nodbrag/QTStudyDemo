
#include "CpuUsageWin.h"

CpuUsageWin::CpuUsageWin()
{
	init();
}

CpuUsageWin::~CpuUsageWin()
{
    delete[] processInfo;
    delete[] cpuPercent;
    delete[] oldIdleTime;
    delete[] oldKerenelTime;
    delete[] oldUserTime;
    delete[] oldDpctTime;
    delete[] oldInterruptTime;
}

int CpuUsageWin::init()
{

    processorCount = getNumberProcessors();
    if (processorCount==-1)
        return -1;

    cpuPercent = new int[processorCount];
    oldIdleTime = new __int64[processorCount];
    memset(oldIdleTime,0,sizeof(__int64)*processorCount);
    oldKerenelTime = new __int64[processorCount];
    memset(oldKerenelTime,0,sizeof(__int64)*processorCount);
    oldUserTime = new __int64[processorCount];
    memset(oldUserTime,0,sizeof(__int64)*processorCount);
    oldDpctTime = new __int64[processorCount];
    memset(oldDpctTime,0,sizeof(__int64)*processorCount);
    oldInterruptTime = new __int64[processorCount];
    memset(oldInterruptTime,0,sizeof(__int64)*processorCount);

    processInfo =new SYSTEM_PROCESSOR_PERFORMANCE_INFORMATION[processorCount];
    return 0;
}


int CpuUsageWin::getNumberProcessors()
{    
	int ProcessorCount = 0;
	int groupCount = GetActiveProcessorGroupCount();
	for (int i = 0; i < groupCount; i++)
	{
		ProcessorCount += GetActiveProcessorCount(i);
	}
	return ProcessorCount;
}


int CpuUsageWin::getUseage(const size_t nNumber)
{
    return cpuPercent[nNumber];
}


void CpuUsageWin::calProcessorsUses()
{
    PROCNTQSI	NtQuerySystemInformation;
    __int64	nIdleTime=0,nKernelTime=0,nUserTime=0,nDpcTime=0,nInterruptTime=0,nTotalTime=0;

    NtQuerySystemInformation = (PROCNTQSI)GetProcAddress(GetModuleHandle(TEXT("ntdll")), "NtQuerySystemInformation");
	if (NtQuerySystemInformation == NULL) {
		goto l_end;
	}

    NtQuerySystemInformation(SystemProcessorPerformanceInformation, processInfo, sizeof(SYSTEM_PROCESSOR_PERFORMANCE_INFORMATION) * processorCount, 0);
    for (int i = 0; i < processorCount; i++)
    {
          nIdleTime = processInfo[i].i64IdleTime - oldIdleTime[i];
          nKernelTime = processInfo[i].i64KernelTime - oldKerenelTime[i];
          nUserTime = processInfo[i].i64UserTime - oldUserTime[i];
          nDpcTime = processInfo[i].i64DpcTime -oldDpctTime[i];
          nInterruptTime = processInfo[i].i64InterruptTime - oldInterruptTime[i];

          nTotalTime = nKernelTime + nUserTime + nDpcTime + nInterruptTime;
          cpuPercent[i] =100*(nTotalTime-nIdleTime)/nTotalTime;

          oldIdleTime[i] = processInfo[i].i64IdleTime;
          oldKerenelTime[i] = processInfo[i].i64KernelTime;
          oldUserTime[i] = processInfo[i].i64UserTime;
          oldDpctTime[i] = processInfo[i].i64DpcTime;
          oldInterruptTime[i] = processInfo[i].i64InterruptTime;
     }

l_end:
	return;
}

float CpuUsageWin::getTemperature(int socketNo)
{
    return 0.0f;
}

int    CpuUsageWin::getSocketCount()
{
    return 0;
}


