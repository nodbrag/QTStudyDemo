#ifndef CTIMER_H
#define CTIMER_H

#include <Windows.h>

class CTimer
{
public:
    __forceinline CTimer()
    {
        QueryPerformanceFrequency(&m_Frequency);
        QueryPerformanceCounter(&m_StartCount);
    }

    __forceinline void reset()
    {
        QueryPerformanceCounter(&m_StartCount);
    }

    __forceinline double end()
    {
        QueryPerformanceCounter(&nCurCount);
        double elapsedTime = static_cast<double>(nCurCount.QuadPart - m_StartCount.QuadPart) /
                m_Frequency.QuadPart * 1000 * 1000 ;
        return elapsedTime;
    }

private:
    LARGE_INTEGER m_Frequency;
    LARGE_INTEGER m_StartCount;
    LARGE_INTEGER nCurCount;
};

#endif // CTIMER_H
