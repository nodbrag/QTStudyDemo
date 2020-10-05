#ifndef SYSTEMTRAYICON_H
#define SYSTEMTRAYICON_H

#include <QObject>
#include <QSystemTrayIcon>

class MessageTipForm;
class QTimer;
class SystemTrayIcon : public QObject
{
    Q_OBJECT
public:
    explicit SystemTrayIcon(QObject *parent = 0);
    ~SystemTrayIcon();

    // 添加收到消息至提示框
    void addToTipList(const QString& name, const QString &text);

private slots:
    // 检测鼠标是否在托盘内部
    void slot_checkTrayIconHover();

    // 修改在线状态
    void slot_modifyState(const QString& state);

    // 退出应用程序
    void slot_quitApp();

    // 托盘图标被激活
    void slot_trayIconActivated(QSystemTrayIcon::ActivationReason reason);

    // 无消息
    void slot_NoMessage();

    void slot_flashingTrayIcon();

private:
    // 创建托盘图标
    void createTrayIcon();

    // 托盘闪烁
    void flashingTrayIcon(const QPixmap& pixmap, int msec=500);

    // 停止托盘闪烁
    void stopFlashingTrayIcon();

private:
    // 窗口消息提示窗口
    MessageTipForm*    _messageTipForm;

    // 检测托盘与鼠标位置定时器
    QTimer*    _checkTimer;

    // 托盘闪烁控制
    bool    _showIcon;
    // 当前托盘图标
    QPixmap    _pixmap;
    // 闪烁定时器
    QTimer*    _flashTimer;

    // 托盘图标对象
    QSystemTrayIcon*    _trayIcon;

    QMenu*    trayIconMenu;

};

#endif // SYSTEMTRAYICON_H
