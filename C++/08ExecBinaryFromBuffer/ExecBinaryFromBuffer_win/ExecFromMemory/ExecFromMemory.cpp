#include <iostream>
#include <windows.h>

//int add(int a, int b)
//{
//	return a + b;
//}

typedef int(*AddFunc)(int, int);

int main()
{
	// int add(int a, int b)函数二进制码
#ifdef _WIN64
	unsigned char add_binaryCode[] = 
	{ 0x89, 0x54, 0x24, 0x10, 0x89, 0x4c, 0x24, 0x08, 0x8b, 0x44, 0x24, 0x10, 0x8b, 0x4c, 0x24, 0x08, 0x03, 0xc8, 0x8b, 0xc1, 0xc3 }; // x64
#else
	unsigned char add_binaryCode[] = { 0x55, 0x8b, 0xec, 0x8b, 0x45, 0x08, 0x03, 0x45, 0x0c, 0x5d, 0xc3 }; // x86
#endif // _WIN64

	// 申请EXECUTE属性内存
	void* execBuf = VirtualAlloc(0, sizeof(add_binaryCode), MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE);

	// 拷贝二进制码
	memcpy(execBuf, add_binaryCode, sizeof(add_binaryCode));

	// 执行二进制码
	AddFunc func = (AddFunc)execBuf;
	int ret = func(1, 2);
	std::cout << "result:" << ret;

	// 释放内存
	VirtualFree(execBuf, 0, MEM_RELEASE);
	return 0;
}