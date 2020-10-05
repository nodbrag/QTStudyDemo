#include "PlayStateMachine.h"
#include <QStateMachine>
#include <QAction>
#include <QSignalTransition>
#include <QEvent>
#include <QDebug>
#include "IPlayer.h"

Q_DECLARE_METATYPE(IPlayer*)

/**
 * @brief The StartCmdProcess class
 * "开始"命令处理类
 */
class StartCmdProcess : public QSignalTransition
{
public:
    StartCmdProcess(QAction* sender)
        :QSignalTransition(sender, SIGNAL(triggered()))
    {}

protected:
    bool eventTest(QEvent *event) override
    {
        if (!QSignalTransition::eventTest(event))
                    return false;

        qDebug() << "StartCmdProcess";

        QAction* sender = static_cast<QAction*>(senderObject());
        IPlayer* player = sender->data().value<IPlayer*>();
        if (player == nullptr)
        {
            qDebug() << "'player' can not be null";
            return false;
        }
        return player->start();
    }
};

/**
 * @brief The PauseCmdProcess class
 * "暂停"命令处理类
 */
class PauseCmdProcess : public QSignalTransition
{
public:
    PauseCmdProcess(QAction* sender)
        :QSignalTransition(sender, SIGNAL(triggered()))
    {}

protected:
    bool eventTest(QEvent *event) override
    {
        if (!QSignalTransition::eventTest(event))
                    return false;

        qDebug() << "PauseCmdProcess";

        QAction* sender = static_cast<QAction*>(senderObject());
        IPlayer* player = sender->data().value<IPlayer*>();
        if (player == nullptr)
        {
            qDebug() << "'player' can not be null";
            return false;
        }
        return player->pause();
    }
};

/**
 * @brief The StopCmdProcess class
 * "停止"命令处理类
 */
class StopCmdProcess : public QSignalTransition
{
public:
    StopCmdProcess(QAction* sender)
        :QSignalTransition(sender, SIGNAL(triggered()))
    {}

protected:
    bool eventTest(QEvent *event) override
    {
        if (!QSignalTransition::eventTest(event))
                    return false;

        qDebug() << "StopCmdProcess";

        QAction* sender = static_cast<QAction*>(senderObject());
        IPlayer* player = sender->data().value<IPlayer*>();
        if (player == nullptr)
        {
            qDebug() << "'player' can not be null";
            return false;
        }
        return player->stop();
    }
};

/**
 * @brief The ResumeCmdProcess class
 * "继续"命令处理类
 */
class ResumeCmdProcess : public QSignalTransition
{
public:
    ResumeCmdProcess(QAction* sender)
        :QSignalTransition(sender, SIGNAL(triggered()))
    {}

protected:
    bool eventTest(QEvent *event) override
    {
        if (!QSignalTransition::eventTest(event))
                    return false;

        qDebug() << "ResumeCmdProcess";

        QAction* sender = static_cast<QAction*>(senderObject());
        IPlayer* player = sender->data().value<IPlayer*>();
        if (player == nullptr)
        {
            qDebug() << "'player' can not be null";
            return false;
        }
        return player->resume();
    }
};

/**
 * @brief PlayStateMachine::PlayStateMachine
 * @param startAction "开始"命令
 * @param stopAction "停止"命令
 * @param player 任务/播放器接口类
 * @param parent 父节点
 */
PlayStateMachine::PlayStateMachine(QAction *startAction,
                                   QAction *stopAction,
                                   IPlayer *player,
                                   QObject *parent)
    : QObject(parent)
{
    // 保存handler
    startAction->setText(tr("Start"));
    stopAction->setText(tr("Stop"));
    startAction->setData(QVariant::fromValue(player));
    stopAction->setData(QVariant::fromValue(player));

    // 创建状态机
    QStateMachine *machine = new QStateMachine(parent);

    /* 创建状态，并配置进入状态时，设置Action属性 */
    QState *readyState = new QState(machine); // 创建"就绪状态"
    readyState->assignProperty(startAction, "text", tr("Start"));
    readyState->assignProperty(stopAction, "enabled", false);

    QState *runningState = new QState(machine); // 创建"运行状态"
    runningState->assignProperty(startAction, "text", tr("Pause"));
    runningState->assignProperty(stopAction, "enabled", true);

    QState *pauseState = new QState(machine); // 创建"暂停状态"
    pauseState->assignProperty(startAction, "text", tr("Resume"));
    pauseState->assignProperty(stopAction, "enabled", true);

    /* 创建状态过渡对象，建立源状态与目的状态过渡关联 */
    // 点击startAction(start)触发，readyState->runningState转换状态
    QSignalTransition* toRunning = new StartCmdProcess(startAction);
    toRunning->setTargetState(runningState);
    readyState->addTransition(toRunning);

    // 点击startAction(pause)触发，runningState->pauseState转换状态
    QSignalTransition* toPause = new PauseCmdProcess(startAction);
    toPause->setTargetState(pauseState);
    runningState->addTransition(toPause);

    // 点击stopAction(stop)触发，runningState->readyState转换状态
    QSignalTransition* toReady = new StopCmdProcess(stopAction);
    toReady->setTargetState(readyState);
    runningState->addTransition(toReady);

    // 点击startAction(resume)触发，pauseState->runningState转换状态
    toRunning = new ResumeCmdProcess(startAction);
    toRunning->setTargetState(runningState);
    pauseState->addTransition(toRunning);

    // 点击stopAction(stop)触发，pauseState->readyState转换状态
    toReady = new StopCmdProcess(stopAction);
    toReady->setTargetState(readyState);
    pauseState->addTransition(toReady);

    // 将readyState设置为状态机的初始状态
    machine->setInitialState(readyState);
    machine->start();
}

PlayStateMachine::~PlayStateMachine()
{

}
