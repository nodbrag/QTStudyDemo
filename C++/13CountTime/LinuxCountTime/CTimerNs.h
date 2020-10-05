#ifndef CTIMERNS_H
#define CTIMERNS_H

#include <time.h>

/**
 * @brief The CTimerNs class
 * linux下时间统计类(ns级)
 */
class CTimerNs
{
public:
    inline CTimerNs()
    {
        clock_gettime(CLOCK_REALTIME, &startTime);
    }

    inline void reset()
    {
        clock_gettime(CLOCK_REALTIME, &startTime);
    }

    inline long long end() // 返回消耗的ns
    {
        clock_gettime(CLOCK_REALTIME, &endTime);
        long long elapsedTime = (endTime.tv_sec - startTime.tv_sec) * 1000 +
                (endTime.tv_nsec - startTime.tv_nsec);
        return elapsedTime;
    }

private:
    struct timespec startTime;
    struct timespec endTime;
};

#endif // CTIMERNS_H
