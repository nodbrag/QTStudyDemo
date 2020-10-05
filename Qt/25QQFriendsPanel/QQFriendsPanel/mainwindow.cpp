#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "PersonList.h"
#include <QHBoxLayout>
#include "PersonListBuddy.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _list = new PersonList();
    connect(_list, SIGNAL(signal_groupMenuEvent(const QPoint&)),
            this, SLOT(slot_groupMenuEvent(const QPoint&)));
    connect(_list, SIGNAL(signal_blankMenuEvent(const QPoint&)),
            this, SLOT(slot_blankMenuEvent(const QPoint&)));
    connect(_list, SIGNAL(signal_buddyMenuEvent(const QPoint&)),
            this, SLOT(slot_buddyMenuEvent(const QPoint&)));
    this->setCentralWidget(_list);

    // 创建菜单
    //初始化：
    blankMenu = new QMenu();
    groupMenu = new QMenu();
    personMenu = new QMenu();
    QAction *addGroup = new QAction("添加分组", this);
    QAction *delGroup = new QAction("删除该组", this);
    QAction *rename = new QAction("重命名", this);
    QAction *addBuddy = new QAction("添加好友",this);
    QAction *delBuddy = new QAction("删除好友", this);

    //布局：
    blankMenu->addAction(addGroup);
    groupMenu->addAction(delGroup);
    groupMenu->addAction(rename);
    groupMenu->addAction(addBuddy);
    personMenu->addAction(delBuddy);

    connect(addGroup,SIGNAL(triggered()),this,SLOT(slotAddGroup()));
    connect(delGroup,SIGNAL(triggered()),this,SLOT(slotDelGroup()));
    connect(rename,SIGNAL(triggered()),this,SLOT(slotRename()));
    connect(addBuddy,SIGNAL(triggered()),this,SLOT(slotAddBuddy()));
    connect(delBuddy,SIGNAL(triggered()),this,SLOT(slotDelBuddy()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slot_groupMenuEvent(const QPoint &point)
{
    groupMenu->exec(point);
}

void MainWindow::slot_blankMenuEvent(const QPoint &point)
{
    blankMenu->exec(point);
}

void MainWindow::slot_buddyMenuEvent(const QPoint &point)
{
    personMenu->exec(point);
}

void MainWindow::slotAddGroup()
{
    _list->addGroupAndEdit();
}

void MainWindow::slotDelGroup()
{
    _list->removeGroup(_list->currentGroup());
}

void MainWindow::slotAddBuddy()
{
    PersonListBuddy *buddy=new PersonListBuddy();   //创建一个自己定义的信息类
    buddy->setHeadPixmap(QPixmap(":/head"));          //设置头像
    buddy->setName("逍遥圣帝");                  //设置用户名
    buddy->setSign("用通俗的语言，讲深刻的技术。");   //设置个性签名
    _list->addBuddy(buddy, _list->currentGroup());
}

void MainWindow::slotDelBuddy()
{
    _list->removeBuddy(_list->currentBuddy());
}

void MainWindow::slotRename()
{
    _list->renameGroup(_list->currentGroup());
}


