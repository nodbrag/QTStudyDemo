#ifndef PERSONLIST_H
#define PERSONLIST_H

#include <QListWidget>

class QMenu;
class QMouseEvent;
class LineEdit;
class PersonListBuddy;

//自定义QListWidget
class PersonList :
        public QListWidget //继承QListWidget，可以使用它本身自带的函数，更方便
{
    Q_OBJECT
public:
    explicit PersonList(QWidget *parent = 0);

    // 添加分组
    bool addGroup(const QString& group);
    void addGroupAndEdit();  // 添加分组并编辑分组名称
    // 删除分组
    void removeGroup(const QString& group);
    // 重命名分组,name - 分组名称
    void renameGroup(const QString& group);

    // 添加好友
    bool addBuddy(PersonListBuddy* buddy, const QString& group);
    // 删除好友
    void removeBuddy(PersonListBuddy* buddy);

    // 获取分组下好友
    QList<PersonListBuddy *> getBuddys(const QString& group);

    // 获取分组数量
    int groupCount();

    // 获取好友数量
    int buddyCount();

    // 获取当前选择的好友对象
    // 若选择分组，则此函数返回NULL
    PersonListBuddy* currentBuddy();

    // 获取当前选择的分组名称
    QString currentGroup();

protected:
    void mousePressEvent(QMouseEvent *event);//鼠标点击事件
    void contextMenuEvent(QContextMenuEvent* event);//菜单事件，为了显示菜单

private slots:
    void slotRenameEditFshed();//命名完成

signals:
    // 分组名称被修改
    void signal_groupNameChanged(const QString& str);

    // 分组右键菜单事件
    void signal_groupMenuEvent(const QPoint& point);

    // 空白处右键菜单事件
    void signal_blankMenuEvent(const QPoint& point);

    // 好友右键菜单事件
    void signal_buddyMenuEvent(const QPoint& point);

private:
    // 获取分组对象指针
    QListWidgetItem* group(const QString& group);

    // 获取好友对象指针
    QListWidgetItem* buddy(PersonListBuddy* buddy);

    // 分组是否已经存在
    bool isExistGroup(const QString& group);

private:
    QMap<QListWidgetItem*,QListWidgetItem*> groupMap;   // 组容器 - key:项 value:组
    QMap<QListWidgetItem*,bool> isHideMap;//用来判断该组是否隐藏了
    LineEdit *groupNameEdit;//组的名字，重命名的时候需要用到
    QListWidgetItem*    _tempRename;  // 保存重命名时，临时分组对象
    QListWidgetItem *currentItem;//当前的项
};

#endif // PERSONLIST_H
