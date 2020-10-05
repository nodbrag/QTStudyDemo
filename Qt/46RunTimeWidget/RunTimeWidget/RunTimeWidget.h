#ifndef RUNTIMEWIDGET_H
#define RUNTIMEWIDGET_H

#include <QWidget>

class QLabel;

/**
 * @brief The RunTimeWidget class
 * 任务运行时间显示控件
 */
class RunTimeWidget : public QWidget
{
    Q_OBJECT
public:
    RunTimeWidget(QWidget* parent = nullptr);

    static QString timeToString(qint64 ms);
    static qint64 stringToTime(const QString& str);

public slots:
    void setCurTime(qint64 ms);
    void setCurTime(QString time);
    void setTotalTime(qint64 ms);
    void setTotalTime(QString time);

private:
    QLabel* curLabel;
    QLabel* totalLabel;
};

#endif // RUNTIMEWIDGET_H
