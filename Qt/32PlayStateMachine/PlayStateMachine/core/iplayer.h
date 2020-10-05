#ifndef IPLAYER_H
#define IPLAYER_H

/**
 * @brief The IPlayer class
 * 任务/播放器接口
 */
class IPlayer
{
public:
    IPlayer() {}
    virtual ~IPlayer() {}

    virtual bool start() = 0;
    virtual bool pause() = 0;
    virtual bool resume() = 0;
    virtual bool stop() = 0;
};

#endif // IPLAYER_H
