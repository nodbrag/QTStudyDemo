#include "Thread2.h"
#include <Windows.h>

void Thread2::run()
{
    // 获取线程id
    quint64 threadId = (quint64)QThread::currentThreadId();

    // 线程id=>线程句柄
    HANDLE handle = OpenThread(THREAD_ALL_ACCESS, false, threadId);

    // 处理器组亲和性结构
    GROUP_AFFINITY group_affinity;
    group_affinity.Reserved[0] = 0;
    group_affinity.Reserved[1] = 0;
    group_affinity.Reserved[2] = 0;
    group_affinity.Mask = 0x04;
    group_affinity.Group = 0x01;

    // 设置线程亲和性
    SetThreadGroupAffinity(handle, &group_affinity, nullptr);

    for (;;)
    {
    }
}
