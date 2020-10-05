#include "RunTimeWidget.h"
#include <QHBoxLayout>
#include <QLabel>

/**
 * @brief RunTimeWidget::RunTimeWidget
 * 创建时间显示label
 * @param parent 父节点
 */
RunTimeWidget::RunTimeWidget(QWidget *parent)
    : QWidget(parent)
{
    QHBoxLayout* layout = new QHBoxLayout(this);
    curLabel = new QLabel("00:00:00", this);
    curLabel->setFrameShape(QFrame::StyledPanel);
    QLabel* sepLabel = new QLabel("/", this);
    totalLabel = new QLabel("00:00:00", this);
    totalLabel->setFrameShape(QFrame::StyledPanel);
    layout->addWidget(curLabel);
    layout->addWidget(sepLabel);
    layout->addWidget(totalLabel);
}

/**
 * @brief RunTimeWidget::setCurTime
 * 设置当前运行时间
 * @param ms 毫秒
 */
void RunTimeWidget::setCurTime(qint64 ms)
{
    curLabel->setText(timeToString(ms));
}

/**
 * @brief RunTimeWidget::setCurTime
 * 设置当前运行时间
 * @param time 时间格式字符串，如"12:02:45"
 */
void RunTimeWidget::setCurTime(QString time)
{
    curLabel->setText(time);
}

/**
 * @brief RunTimeWidget::setTotalTime
 * 设置运行总时长
 * @param ms 毫秒
 */
void RunTimeWidget::setTotalTime(qint64 ms)
{
    totalLabel->setText(timeToString(ms));
}

/**
 * @brief RunTimeWidget::setTotalTime
 * 设置运行总时长
 * @param time 时间格式字符串，如"12:02:45"
 */
void RunTimeWidget::setTotalTime(QString time)
{
    totalLabel->setText(time);
}

/**
 * @brief RunTimeWidget::timeToString
 * 数值型时间值转换为字符串，如1000ms=>"00:00:01"
 * @param ms 毫秒
 * @return 时间字符串
 */
QString RunTimeWidget::timeToString(qint64 ms)
{
    int ss = 1000;
    int mi = ss * 60;
    int hh = mi * 60;

    qint64 hour = ms / hh;
    qint64 minute = (ms - hour * hh) / mi;
    qint64 second = (ms - hour * hh - minute * mi) / ss;
    qint64 milliSecond = ms % ss;

    QString hou = ((hour < 10) ? "0" : "") + QString::number(hour,10);
    QString min = ((minute < 10) ? "0" : "") + QString::number(minute,10);
    QString sec = ((second < 10) ? "0" : "") + QString::number(second,10);
    QString msec = ((milliSecond < 10) ? "0" : "") + QString::number(milliSecond,10);

    return hou + ":" + min + ":" + sec ;
}

/**
 * @brief RunTimeWidget::stringToTime
 * 时间字符串转换为数值型时间值，如"00:00:01"=>1000ms
 * @param str 时间字符串
 * @return 数值型时间值ms
 */
qint64 RunTimeWidget::stringToTime(const QString &str)
{
    QStringList strs = str.split(":");
    if (strs.size() != 3)
    {
        return 0;
    }

    int ss = 1000;
    int mi = ss * 60;
    int hh = mi * 60;

    qint64 ms = 0;
    ms += strs.at(0).toInt() * hh;
    ms += strs.at(1).toInt() * mi;
    ms += strs.at(2).toInt() * ss;
    return ms;
}

