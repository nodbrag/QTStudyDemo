#include "TaskPlayer.h"
#include <QDebug>

TaskPlayer::TaskPlayer()
{
}

TaskPlayer::~TaskPlayer()
{
}

bool TaskPlayer::start()
{
    qDebug() << "do start command...";
    return true;
}

bool TaskPlayer::pause()
{
    qDebug() << "do pause command...";
    return true;
}

bool TaskPlayer::resume()
{
    qDebug() << "do resume command...";
    return true;
}

bool TaskPlayer::stop()
{
    qDebug() << "do stop command...";
    return true;
}
