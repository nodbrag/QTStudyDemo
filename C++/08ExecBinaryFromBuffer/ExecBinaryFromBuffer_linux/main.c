#include <stdio.h>
#include <string.h>
#include <sys/mman.h>

//int add(int a, int b)
//{
//	return a + b;
//}

typedef int(*AddFunc)(int, int);

int main() 
{
    // int add(int a, int b)函数64位系统下二进制码
	unsigned char add_binaryCode[] = {
		0x55,
		0x48, 0x89, 0xe5,
		0x89, 0x7d, 0xfc,
		0x89, 0x75, 0xf8,
		0x8b, 0x55, 0xfc,
		0x8b, 0x45, 0xf8,
		0x01, 0xd0,
		0x5d,
		0xc3
	};

	// 申请EXECUTE属性内存
	void* execBuf = mmap(NULL, sizeof(add_binaryCode), PROT_WRITE | PROT_EXEC,MAP_ANON | MAP_PRIVATE, -1, 0);

	// 拷贝二进制码
	memcpy(execBuf, add_binaryCode, sizeof(add_binaryCode));

	// 执行二进制码
	AddFunc func = (AddFunc)execBuf;
	int ret = func(1, 2);
	printf("result:%d\n", ret);

	// 释放内存
	munmap(execBuf, sizeof(add_binaryCode));
	return 0;
}