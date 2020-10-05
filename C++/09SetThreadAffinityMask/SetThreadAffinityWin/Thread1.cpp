#include "Thread1.h"
#include <Windows.h>

void Thread1::run()
{
    // 获取线程id
    quint64 threadId = (quint64)QThread::currentThreadId();

    // 线程id=>线程句柄
    HANDLE handle = OpenThread(THREAD_ALL_ACCESS, false, threadId);

    // 设置线程亲和性
    SetThreadAffinityMask(handle, 0x02);

    for (;;)
    {
    }
}
