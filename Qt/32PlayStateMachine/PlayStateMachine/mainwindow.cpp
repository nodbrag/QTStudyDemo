#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMenuBar>
#include "PlayStateMachine.h"
#include "TaskPlayer.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QMenu *taskMenu = menuBar()->addMenu(tr("Task"));
    QToolBar* taskToolBar = addToolBar(tr("Task"));

    QAction* startAction = taskMenu->addAction(tr("Start"));
    QAction* stopAction = taskMenu->addAction(tr("Stop"));

    taskToolBar->addAction(startAction);
    taskToolBar->addAction(stopAction);

    player = new TaskPlayer();

    // 创建并启动状态机管理器
    new PlayStateMachine(startAction, stopAction, player, this);
}

MainWindow::~MainWindow()
{
    delete player;
    delete ui;
}
