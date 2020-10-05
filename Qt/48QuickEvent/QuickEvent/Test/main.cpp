#include "mainwindow.h"
#include <QApplication>
#include <QDebug>
#include "quickcontroller.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qDebug() << "main thread id :" << QThread::currentThreadId();

    QuickController controller;

    MainWindow w;
    w.show();

    return a.exec();
}
