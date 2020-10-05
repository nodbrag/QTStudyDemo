#include <iostream>
#include "CpuUsage/CpuUsageWin.h"

using namespace std;

//#include <windows.h>
//#include <stdio.h>
//#pragma comment(lib, "user32.lib")

void main()
{
	CpuUsageWin cpu;
	cpu.calProcessorsUses();

	for (int i = 0; i < cpu.getNumberProcessors(); i++)
	{
		cout << "cpu" << i << ":" << cpu.getUseage(i) << endl;
	}

	getchar();

	/*
	SYSTEM_INFO siSysInfo;

	// Copy the hardware information to the SYSTEM_INFO structure. 

	GetSystemInfo(&siSysInfo);

	// Display the contents of the SYSTEM_INFO structure. 

	printf("Hardware information: \n");
	printf("  OEM ID: %u\n", siSysInfo.dwOemId);
	printf("  Number of processors: %u\n",
		siSysInfo.dwNumberOfProcessors);
	printf("  Page size: %u\n", siSysInfo.dwPageSize);
	printf("  Processor type: %u\n", siSysInfo.dwProcessorType);
	printf("  Minimum application address: %lx\n",
		siSysInfo.lpMinimumApplicationAddress);
	printf("  Maximum application address: %lx\n",
		siSysInfo.lpMaximumApplicationAddress);
	printf("  Active processor mask: %u\n",
		siSysInfo.dwActiveProcessorMask);
	*/

}