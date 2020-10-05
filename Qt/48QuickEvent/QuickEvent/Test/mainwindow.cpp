#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include "quickapplication.h"
#include "childdialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    childDialog = new ChildDialog(this);
    childDialog->show();

    QuickApplication::subscibeEvent(this, "show_time");
    QuickApplication::subscibeEvent(this, "student_event");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::event_show_time(const QDateTime &time)
{
    qDebug() << "recv time:" << time.toString();
}

void MainWindow::event_student_event(const Student &stu)
{
    qDebug() << "recv student:" << stu.name_ << stu.id_;
}
