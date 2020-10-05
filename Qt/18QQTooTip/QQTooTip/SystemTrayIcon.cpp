#include "SystemTrayIcon.h"
#include <QTimer>
#include <QSystemTrayIcon>
#include <QSignalMapper>
#include <QMessageBox>
#include <QApplication>
#include <QAction>
#include <QMenu>
#include "MessageTipForm.h"

SystemTrayIcon::SystemTrayIcon(QObject *parent) :
    QObject(parent),
    _showIcon(false)
{
    createTrayIcon();

    // 检测鼠标位置定时器
    _checkTimer = new QTimer(this);
    connect(_checkTimer, SIGNAL(timeout()), this, SLOT(slot_checkTrayIconHover()));
    _checkTimer->setInterval(200);

    // 托盘图标闪烁定时器
    _flashTimer = new QTimer(this);
    connect(_flashTimer, SIGNAL(timeout()), this, SLOT(slot_flashingTrayIcon()));

    // 创建消息盒子窗口
    _messageTipForm = new MessageTipForm();
    QPoint leftBottom;
    {
        QRect rect = _trayIcon->geometry();
        QPoint trayIconPos = QPoint(rect.left() + rect.width()/2-1, rect.top() + rect.height()/2-1);
        leftBottom = QPoint(trayIconPos.x() - _messageTipForm->width()/2+1,
                                trayIconPos.y() - 19);
    }
    _messageTipForm->setFixedLeftBottom(leftBottom);
    connect(_messageTipForm, SIGNAL(signal_NoMessage()), this, SLOT(slot_NoMessage()));
}

SystemTrayIcon::~SystemTrayIcon()
{
    delete trayIconMenu;
    trayIconMenu = NULL;

    delete _messageTipForm;
    _messageTipForm = NULL;
}

void SystemTrayIcon::slot_checkTrayIconHover()
{
    // 获取消息盒子全局rect
    QPoint pos = _messageTipForm->mapToGlobal(QPoint(0, 0));
    QSize size = _messageTipForm->size();
    QRect rectForm = QRect(pos, size);

    // 若鼠标在图片图标内，或鼠标在消息盒子内
    QRect rect = _trayIcon->geometry();
    if (rect.contains(QCursor::pos()) ||
            (rectForm.contains(QCursor::pos()) && !_messageTipForm->isHidden()))
    {
        _messageTipForm->show();
        _messageTipForm->activateWindow();
    }
    else
    {
        _messageTipForm->hide();
    }
}

void SystemTrayIcon::flashingTrayIcon(const QPixmap &pixmap, int msec)
{
    // 开始闪烁
    _pixmap = pixmap;
    if (_flashTimer->isActive())
        _flashTimer->stop();
    _flashTimer->setInterval(msec);
    _flashTimer->start();

    // 开始检测鼠标与托盘区域
    _checkTimer->start();
}

void SystemTrayIcon::stopFlashingTrayIcon()
{
    _trayIcon->setIcon(QIcon(":/res/app.ico"));
    if (_flashTimer->isActive())
        _flashTimer->stop();

    if (_checkTimer->isActive())
        _checkTimer->stop();

    _messageTipForm->hide();
}

void SystemTrayIcon::addToTipList(const QString &name, const QString &text)
{
    _messageTipForm->addToTipList(name, text);
    flashingTrayIcon(QPixmap(":/res/app.ico"));
}

void SystemTrayIcon::slot_modifyState(const QString &state)
{
    QMessageBox::warning(NULL, "提示", state);
}

void SystemTrayIcon::slot_quitApp()
{
    qApp->exit(0);
}

void SystemTrayIcon::createTrayIcon()
{
    // 创建托盘对象
    _trayIcon = new QSystemTrayIcon(this);
    _trayIcon->setIcon(QIcon(":/res/app.ico"));
    _trayIcon->setToolTip("测试程序");

    connect(_trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
        this, SLOT(slot_trayIconActivated(QSystemTrayIcon::ActivationReason)));

    // 建立信号槽
    QSignalMapper* trayMap = new QSignalMapper(this);
    connect(trayMap, SIGNAL(mapped(const QString&)), this, SLOT(slot_modifyState(const QString&)));

    //创建托盘图标中的各个按钮，并连接信号/糟
    QAction* onlineAction = new QAction(tr("在线"), this);
    connect(onlineAction, SIGNAL(triggered()), trayMap, SLOT(map()));
    trayMap->setMapping(onlineAction, "在线");

    QAction* talkAction = new QAction(tr("Q我吧"), this);
    connect(talkAction, SIGNAL(triggered()), trayMap, SLOT(map()));
    trayMap->setMapping(talkAction, "Q我吧");

    QAction* busyAction = new QAction(tr("忙碌"), this);
    connect(busyAction, SIGNAL(triggered()), trayMap, SLOT(map()));
    trayMap->setMapping(busyAction, "忙碌");

    QAction* leaveAction = new QAction(tr("离开"), this);
    connect(leaveAction, SIGNAL(triggered()), trayMap, SLOT(map()));
    trayMap->setMapping(leaveAction, "离开");

    QAction* disturbAction = new QAction(tr("请勿打扰"), this);
    connect(disturbAction, SIGNAL(triggered()), trayMap, SLOT(map()));
    trayMap->setMapping(disturbAction, "请勿打扰");

    QAction* stealthAction = new QAction(tr("隐身"), this);
    connect(stealthAction, SIGNAL(triggered()), trayMap, SLOT(map()));
    trayMap->setMapping(stealthAction, "隐身");

    QAction* quitAction = new QAction(tr("退出"), this);
    connect(quitAction, SIGNAL(triggered()), this, SLOT(slot_quitApp()));

    //将各个按钮加入到托盘菜单中
    trayIconMenu = new QMenu();
    trayIconMenu->addAction(onlineAction);
    trayIconMenu->addAction(talkAction);
    trayIconMenu->addAction(busyAction);
    trayIconMenu->addAction(leaveAction);
    trayIconMenu->addAction(disturbAction);
    trayIconMenu->addAction(stealthAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(quitAction);
    _trayIcon->setContextMenu(trayIconMenu);

    _trayIcon->show();
}

void SystemTrayIcon::slot_trayIconActivated(QSystemTrayIcon::ActivationReason reason)
{
    if(QSystemTrayIcon::Trigger == reason)
    {
        QMessageBox::warning(NULL, "提示", "激活托盘，此处应该弹出程序");
    }
}

void SystemTrayIcon::slot_flashingTrayIcon()
{
    if (_showIcon)
    {
        _trayIcon->setIcon(QIcon());
        _showIcon = false;
    }
    else
    {
        _trayIcon->setIcon(QIcon(_pixmap));
        _showIcon = true;
    }
}

void SystemTrayIcon::slot_NoMessage()
{
    stopFlashingTrayIcon();
}
