#include "mainwindow.h"
#include <QDebug>
#include "ui_mainwindow.h"
#include "Controller.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    qDebug() << "main thread:" << QThread::currentThreadId();

    Controller* controller = new Controller(this);
    emit controller->operate("copy");
}

MainWindow::~MainWindow()
{
    delete ui;
}
