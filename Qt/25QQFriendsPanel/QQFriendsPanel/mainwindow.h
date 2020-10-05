#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}
class PersonList;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    // 分组右键菜单事件
    void slot_groupMenuEvent(const QPoint& point);

    // 空白处右键菜单事件
    void slot_blankMenuEvent(const QPoint& point);

    // 好友右键菜单事件
    void slot_buddyMenuEvent(const QPoint& point);

    void slotAddGroup();   //添加组
    void slotDelGroup();   //删除组
    void slotAddBuddy();   //添加好友
    void slotDelBuddy();   //删除好友
    void slotRename();     //重命名组

private:
    Ui::MainWindow *ui;

    PersonList*    _list;

    QMenu *blankMenu;//点击空白上的菜单
    QMenu *groupMenu;//点击组上的菜单
    QMenu *personMenu;//点击人上的菜单
};

#endif // MAINWINDOW_H
