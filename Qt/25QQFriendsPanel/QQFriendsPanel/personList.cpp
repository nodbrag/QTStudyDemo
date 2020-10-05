#include "Personlist.h"
#include <QAction>
#include <QIcon>
#include <QMenu>
#include <QMouseEvent>
#include <QLineEdit>
#include <QMessageBox>
#include "PersonListbuddy.h"

// 解决响应editingFinished信号槽中弹出messageBox，造成触发2次editingFinished信号的问题
class LineEdit :
        public QLineEdit
{
public:
    LineEdit(QWidget * parent = 0)
        : QLineEdit(parent) {}
    ~LineEdit(){}

protected:
    virtual void focusOutEvent(QFocusEvent * e)
    {
        QLineEdit::focusOutEvent(e);
        if (e->reason() == Qt::ActiveWindowFocusReason)
        {
            return;
        }
        else
        {
            QLineEdit::focusOutEvent(e);
        }
    }
};

PersonList::PersonList(QWidget *parent) :
    QListWidget(parent),
    _tempRename(NULL),
    currentItem(NULL)
{
    setFocusPolicy(Qt::NoFocus);       // 去除item选中时的虚线边框
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//水平滚动条关闭

    this->setObjectName("PersonList");
    this->setStyleSheet(
             "   QListWidget#PersonList{"
             "       background:white;"
             "       color:black;"
             "       border:none;"
             "   }"

             "   QListWidget#PersonList::item{"
             "       border:none;"
             "           height: 54px;"
             "   }"

             "   QListWidget#PersonList::item:hover{"
             "       background:rgb(252,240,193)"
             "   }"

             "   QListWidget#PersonList::item:selected{"
             "       background:rgb(252,233,161);"
             "       color:black;"
             "   }"

             "   QScrollBar:vertical {     "
             "       background:transparent;"
             "       width:9px;"
             "       margin: 0px 0px 2px 0px;"
             "   }"

             "   QScrollBar::handle:vertical {"
             "       background: rgb(195, 195, 195);"
             "       min-height: 20px;"
             "       border-radius: 3px;"
             "   }"

             "   QScrollBar::handle:vertical:hover{"
             "       background:rgba(0,0,0,30%);"
             "   }"

             "   QScrollBar::add-line:vertical {"
             "       height: 0px;"
             "       subcontrol-position: bottom;"
             "       subcontrol-origin: margin;"
             "   }"

             "   QScrollBar::sub-line:vertical {"
             "       height: 0px;"
             "       subcontrol-position: top;"
             "       subcontrol-origin: margin;"
             "   }"
                );

    //初始化：
    groupNameEdit=new LineEdit();

    //设置：
    groupNameEdit->setParent(this);  //设置父类
    groupNameEdit->hide(); //设置初始时隐藏
    groupNameEdit->setPlaceholderText("未命名");//设置初始时的内容

    //信息槽：
    connect(groupNameEdit,SIGNAL(editingFinished()),this,SLOT(slotRenameEditFshed()));
}

bool PersonList::addGroup(const QString &group)
{
    // 检测是否重名
    QMap<QListWidgetItem*,bool>::iterator it;
    for (it = isHideMap.begin(); it != isHideMap.end(); it++)
    {
        if (it.key()->text() == group)
            return false;  // 分组重名
    }

    QListWidgetItem *newItem=new QListWidgetItem(QIcon(":/arrowRight"), group);    //创建一个Item
    newItem->setSizeHint(QSize(this->width(),25));//设置宽度、高度
    this->addItem(newItem);         //加到QListWidget中

    groupMap.insert(newItem,newItem);//加到容器groupMap里，key和value都为组
    isHideMap.insert(newItem,true);  //设置该组隐藏状态
    return true;
}

void PersonList::addGroupAndEdit()
{
    QListWidgetItem *newItem=new QListWidgetItem(QIcon(":/arrowRight"), "");    //创建一个Item
    newItem->setSizeHint(QSize(this->width(),25));//设置宽度、高度
    this->addItem(newItem);         //加到QListWidget中

    groupMap.insert(newItem,newItem);//加到容器groupMap里，key和value都为组
    isHideMap.insert(newItem,true);  //设置该组隐藏状态

    groupNameEdit->raise();
    //groupNameEdit->setText(tr("未命名")); //设置默认内容
    groupNameEdit->selectAll();        //设置全选
    groupNameEdit->setGeometry(this->visualItemRect(newItem).left()+15,
                               this->visualItemRect(newItem).top()+1,
                               this->visualItemRect(newItem).width(),
                               this->visualItemRect(newItem).height()-2);//出现的位置
    groupNameEdit->show();              //显示
    groupNameEdit->setFocus();          //获取焦点

    _tempRename = newItem;
    currentItem = newItem;
}

void PersonList::removeGroup(const QString &group)
{
    // 找到分组对象
    QListWidgetItem* groupItem = this->group(group);

    if (groupItem == NULL)    return;

    // 移除分组对象及旗下的好友
    this->removeItemWidget(groupItem);
    foreach(QListWidgetItem* temp, groupMap.keys(groupItem))  //遍历该组的所有好友和自身的组
    {
        groupMap.remove(temp);   //移除
        delete temp;   //删除
    }
    isHideMap.remove(groupItem); //移除
}

void PersonList::renameGroup(const QString &group)
{
    QListWidgetItem* item = this->group(group);
    if (item == NULL)    return;

    groupNameEdit->raise();
    groupNameEdit->setGeometry(this->visualItemRect(item).left()+15,
                               this->visualItemRect(item).top()+1,
                               this->visualItemRect(item).width(),
                               this->visualItemRect(item).height()-2);//出现的位置
    groupNameEdit->setText(item->text());   //获取该组名内容
    groupNameEdit->show();                        //显示
    groupNameEdit->selectAll();                   //全选
    groupNameEdit->setFocus();                        //获取焦点

    _tempRename = item;
    currentItem = item;
}

bool PersonList::addBuddy(PersonListBuddy *buddy, const QString &group)
{
    // 找到分组对象
    QListWidgetItem* groupItem = this->group(group);

    if (groupItem == NULL)  // 没有该分组就新建一个
    {
        addGroup(group);
        groupItem = this->group(group);
    }

    QList<QListWidgetItem*> temp = groupMap.keys(groupItem);//当前组对应的项（包括组本身和好友）复制给temp

    //关键代码
    QListWidgetItem *newItem = new QListWidgetItem();       //创建一个newItem
    this->insertItem(row(groupItem)+temp.count(),newItem); //将该newItem插入到后面
    this->setItemWidget(newItem, buddy); //将buddy赋给该newItem
    groupMap.insert(newItem,groupItem);   //加进容器，key为好友，value为组
    if(isHideMap.value(groupItem))          //如果该组是隐藏，则加进去的好友设置为隐藏
        newItem->setHidden(true);
    else                                      //否则，该好友设置为显示
        newItem->setHidden(false);
    return true;
}

void PersonList::removeBuddy(PersonListBuddy *buddy)
{
    // 找到好友对象
    QListWidgetItem* item = this->buddy(buddy);

    if (item == NULL)    return;

    this->removeItemWidget(item);
    groupMap.remove(item);  //移除该好友
    delete item;            //删除
}

QList<PersonListBuddy *> PersonList::getBuddys(const QString &group)
{
    QList<PersonListBuddy *> buddys;

    // 找到分组对象
    QListWidgetItem* groupItem = this->group(group);
    if (groupItem == NULL)    return buddys;

    QList<QListWidgetItem *>  items = groupMap.keys(groupItem);//当前组对应的项（包括组本身和好友）
    for (int i = 1; i < items.size(); i++)  // 去掉头上的组对象
    {
        PersonListBuddy* temp = (PersonListBuddy*)this->itemWidget(items.at(i));
        buddys.push_back(temp);
    }
    return buddys;
}

int PersonList::groupCount()
{
    return isHideMap.size();
}

int PersonList::buddyCount()
{
    return (groupMap.size() - isHideMap.size());
}

PersonListBuddy *PersonList::currentBuddy()
{
    QMap<QListWidgetItem*,bool>::const_iterator it = isHideMap.find(currentItem);
    if (it == isHideMap.end())
    {
        return (PersonListBuddy*)this->itemWidget(currentItem);
    }
    else
        return NULL;
}

QString PersonList::currentGroup()
{
    QMap<QListWidgetItem*,bool>::const_iterator it = isHideMap.find(currentItem);
    if (it != isHideMap.end())
    {
        return currentItem->text();
    }

    QMap<QListWidgetItem*,QListWidgetItem*>::const_iterator iter = groupMap.find(currentItem);
    if (iter != groupMap.end())
    {
        return iter.value()->text();
    }

    return "";
}

QListWidgetItem *PersonList::group(const QString &group)
{
    QListWidgetItem* item = NULL;
    QMap<QListWidgetItem*,bool>::iterator it;
    for (it = isHideMap.begin(); it != isHideMap.end(); it++)
    {
        if (it.key()->text() == group)
        {
            item = it.key();
            break;
        }
    }
    return item;
}

QListWidgetItem *PersonList::buddy(PersonListBuddy *buddy)
{
    QListWidgetItem* item = NULL;
    QMap<QListWidgetItem*,QListWidgetItem*>::iterator it;
    for (it = groupMap.begin(); it != groupMap.end(); it++)
    {
        QListWidgetItem* temp = it.key();
        if (this->itemWidget(temp) == buddy)
        {
            item = temp;
            break;
        }
    }
    return item;
}

bool PersonList::isExistGroup(const QString &group)
{
    bool exist = false;
    QMap<QListWidgetItem*,bool>::iterator it;
    for (it = isHideMap.begin(); it != isHideMap.end(); it++)
    {
        if (it.key()->text() == group)
        {
            exist = true;
            break;
        }
    }
    return exist;
}

//鼠标点击事件
void PersonList::mousePressEvent(QMouseEvent *event)
{
    // 如果不调用基类mousePressEvent，item被select会半天不响应,调用父类，让QSS起效，
    // 因为QSS基于父类QListWidget，子类就是子窗口，就是最上层窗口，是覆盖在父窗口上的，所以先于父窗口捕获消息
    QListWidget::mousePressEvent(event);

    //防止一种特殊情况：给新item命名、点击其他item或空白处时，指向新item的currentItem被赋予其他item
    if(groupNameEdit->isVisible() && !(groupNameEdit->rect().contains(event->pos())))
    {
        emit groupNameEdit->editingFinished();
//        if(groupNameEdit->text()!=NULL)
//            currentItem->setText(groupNameEdit->text());
//        groupNameEdit->setText("");
//        groupNameEdit->hide();
    }

    currentItem = this->itemAt(mapFromGlobal(QCursor::pos()));//鼠标位置的Item，不管右键左键都获取
    if(event->button()==Qt::LeftButton &&
            currentItem!=NULL &&
            currentItem==groupMap.value(currentItem))//如果点击的左键并且是点击的是组
    {
        if(isHideMap.value(currentItem))                                  //如果先前是隐藏，则显示
        {
            foreach(QListWidgetItem* subItem, groupMap.keys(currentItem))//遍历组的对应的项（包括自身和好友）
                if(subItem!=currentItem)                                 //如果是组的话不进行处理
                {
                    subItem->setHidden(false);                            //好友全部显示
                }
            isHideMap.insert(currentItem,false);                          //设置该组为显示状态
            currentItem->setIcon(QIcon(":/arrowDown"));
        }
        else                                                             //否则，先前是显示，则隐藏
        {
            foreach(QListWidgetItem* subItem, groupMap.keys(currentItem))//遍历组的对应的项（包括自身和好友）
                if(subItem!=currentItem)                                 //如果是组的话不进行处理
                {
                    subItem->setHidden(true);                            //好友全部隐藏
                }
             isHideMap.insert(currentItem,true);                          //设置该组为隐藏状态
             currentItem->setIcon(QIcon(":/arrowRight"));
        }
    }
}

//菜单事件，为了显示菜单，点击鼠标右键响应，鼠标点击事件mousePressEvent优先于contextMenuEvent
void PersonList::contextMenuEvent(QContextMenuEvent *event)
{
    QListWidget::contextMenuEvent(event);           //调用基类事件
    if(currentItem==NULL)                           //如果点击到的是空白处
    {
        emit signal_blankMenuEvent(QCursor::pos());
        return;
    }
    if(currentItem==groupMap.value(currentItem))    // 如果点击到的是组
        emit signal_groupMenuEvent(QCursor::pos());
    else                                            //否则点击到的是好友
        emit signal_buddyMenuEvent(QCursor::pos());
}

//重命名完成
void PersonList::slotRenameEditFshed()
{
    if (_tempRename == NULL)    return;

    bool renameSucceed = false;
    QString groupStr = groupNameEdit->text();
    if (groupStr == "")
    {
        //QMessageBox::warning(NULL, "提示", "分组名称不能为空!");
    }
    else
    {
        if (isExistGroup(groupStr))  // 分组重名
        {
            //QMessageBox::warning(NULL, "提示", "分组名称不能重复!");
        }
        else
        {
            _tempRename->setText(groupStr);  //更新组名
            emit signal_groupNameChanged(groupStr);
            renameSucceed = true;
        }
    }
    groupNameEdit->setText("");
    groupNameEdit->hide();  //隐藏重命名编辑框

    // 新建分组且重命名失败时，需要删除新建分组的数据
    if (!renameSucceed && _tempRename->text() == "")
    {
        removeGroup("");
    }
    _tempRename = NULL;
}
