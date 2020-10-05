#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Controller.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _cotroller = new Controller();
    _cotroller->operate("123");
    _cotroller->other();
}

MainWindow::~MainWindow()
{
    delete _cotroller;
    delete ui;
}
