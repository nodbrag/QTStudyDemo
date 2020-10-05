#ifndef CTIMER_H
#define CTIMER_H

#include <sys/time.h>

/**
 * @brief The CTimer class
 * linux下时间统计类(us级)
 */
class CTimer
{
public:
    inline CTimer()
    {
        gettimeofday(&startTime, nullptr);
    }

    inline void reset()
    {
        gettimeofday(&startTime, nullptr);
    }

    inline double end() // 返回消耗的us
    {
        gettimeofday(&endTime, nullptr);
        double elapsedTime = (endTime.tv_sec - startTime.tv_sec) * 1000 * 1000 +
                        (endTime.tv_usec - startTime.tv_usec);
        return elapsedTime;
    }

private:
    struct timeval startTime, endTime;
};

#endif // CTIMER_H
