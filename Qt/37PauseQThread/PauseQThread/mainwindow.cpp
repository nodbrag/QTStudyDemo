#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include "Executor.h"
#include "IRunable.h"

class Task1 : public IRunable
{
public:
    virtual void exec() override
    {
        qDebug() << "do Task1...";
    }
};

class Task2 : public IRunable
{
public:
    virtual void exec() override
    {
        qDebug() << "do Task2...";
    }
};

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    executor = new Executor();
    executor->setStartupDelay(1000);
    executor->setIntervalDelay(1000);

    runableList.append(new Task1());
    runableList.append(new Task2());
    executor->addRunables(runableList);
}

MainWindow::~MainWindow()
{
    delete executor;
    executor = nullptr;
    qDeleteAll(runableList);
    runableList.clear();
    delete ui;
}

void MainWindow::on_pushButton_start_clicked()
{
    executor->start();
}

void MainWindow::on_pushButton_pause_clicked()
{
    executor->pause();
}

void MainWindow::on_pushButton_stop_clicked()
{
    executor->stop();
}

void MainWindow::on_pushButton_resume_clicked()
{
    executor->resume();
}

void MainWindow::on_pushButton_clicked()
{
    Thread::State s = executor->state();
    if (s == Thread::Stoped)
    {
        qDebug() << "state : Stoped";
    }
    else if (s == Thread::Running)
    {
        qDebug() << "state : Running";
    }
    else if (s == Thread::Paused)
    {
        qDebug() << "state : Paused";
    }
}
