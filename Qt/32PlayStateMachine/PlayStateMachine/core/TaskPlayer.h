#ifndef TASKPLAYER_H
#define TASKPLAYER_H

#include "IPlayer.h"

/**
 * @brief The TaskPlayer class
 * 接口实现
 */
class TaskPlayer : public IPlayer
{
public:
    TaskPlayer();
    virtual ~TaskPlayer();

    virtual bool start() override;
    virtual bool pause() override;
    virtual bool resume() override;
    virtual bool stop() override;
};

#endif // TASKPLAYER_H
