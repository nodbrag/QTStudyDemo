#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "RunTimeWidget.h"

#define HOUR    (60*60*1000)

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    RunTimeWidget* widget = new RunTimeWidget(statusBar());
    widget->setTotalTime(240*HOUR);
    widget->setCurTime(2*HOUR);
    statusBar()->addWidget(widget);
    statusBar()->setStyleSheet(QString("QStatusBar::item{border: 0px}"));
}

MainWindow::~MainWindow()
{
    delete ui;
}
