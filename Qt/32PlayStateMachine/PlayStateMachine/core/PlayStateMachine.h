#ifndef PLAYSTATEMACHINE_H
#define PLAYSTATEMACHINE_H

#include <QObject>

class QAction;
class IPlayer;

/**
 * @brief The PlayStateMachine class
 * 播放状态机管理类，将常见的任务/播放器的操作命令：
 * start、pause、resume、stop间状态切换封装进此类，外部无需关心内部实现。
 * 使用时，提供2个QAction作为start、stop命令控件，其中start控件会自动根据状态修改其标题为
 * start、pause、resume中某一个，点击这2个控件共发出4个命令，会自动调用IPlayer对应4个接口。
 * 所以需要将任务/播放器继承自IPlayer，实现所有接口，再将指针传进去，就可以。
 * 注：被调IPlayer接口，根据返回值确定操作成功与否，失败则不会发生状态切换。
 * 如IPlayer->start() == false，则startAction仍然显示"start"，不会显示为"pause"。
 */
class PlayStateMachine : public QObject
{
    Q_OBJECT
public:
    PlayStateMachine(QAction* startAction,
                     QAction* stopAction,
                     IPlayer* player,
                     QObject* parent = nullptr);
    virtual ~PlayStateMachine();
};

#endif // PLAYSTATEMACHINE_H
