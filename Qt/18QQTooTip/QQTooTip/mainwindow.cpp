#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "SystemTrayIcon.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _trayIcon = new SystemTrayIcon();
    _trayIcon->addToTipList("张三", "张三");
    _trayIcon->addToTipList("张三xx", "张三xx");
}

MainWindow::~MainWindow()
{
    delete _trayIcon;
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    _trayIcon->addToTipList("张三xx", "张三xx");
}
