#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMenuBar>
#include <QMenu>
#include <QToolBar>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QMenu* menu = menuBar()->addMenu("Menu");
    QToolBar* toolBar = addToolBar("ToolBar");

    QAction* startAction = menu->addAction("start");
    QAction* pauseAction = menu->addAction("pause");
    pauseAction->setVisible(false);

    toolBar->addAction(startAction);
    toolBar->addAction(pauseAction);

    // 实现自动反转action
    connect(startAction, &QAction::triggered, [=] {
        startAction->setVisible(false);
        pauseAction->setVisible(true);
    });
    connect(pauseAction, &QAction::triggered, [=] {
        pauseAction->setVisible(false);
        startAction->setVisible(true);
    });

    // 正常信号处理
    connect(startAction, &QAction::triggered, this, &MainWindow::onStartActionClicked);
    connect(pauseAction, &QAction::triggered, this, &MainWindow::onPauseActionClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onStartActionClicked()
{
    qDebug() << "start play...";
}

void MainWindow::onPauseActionClicked()
{
    qDebug() << "pause play";
}
