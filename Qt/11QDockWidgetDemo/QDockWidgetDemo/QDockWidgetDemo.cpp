#include "QDockWidgetDemo.h"
#include <QtWidgets>

QDockWidgetDemo::QDockWidgetDemo(QWidget *parent)
    : QMainWindow(parent)
{
    // 创建主窗口edit控件
    mainTextEdit = new QTextEdit();
    mainTextEdit->setText("Main Window");
    mainTextEdit->setAlignment(Qt::AlignCenter);
    setCentralWidget(mainTextEdit);

    // 创建停靠窗口1
    QDockWidget* dock1 = new QDockWidget(tr("DockWindow1"), this);
    dock1->setFeatures(QDockWidget::DockWidgetMovable);
    dock1->setAllowedAreas(Qt::LeftDockWidgetArea|Qt::RightDockWidgetArea);
    QTextEdit* text1 = new QTextEdit();
    text1->setText("Window1");
    dock1->setWidget(text1);
    this->addDockWidget(Qt::LeftDockWidgetArea, dock1);

    // 创建停靠窗口2
    QDockWidget* dock2 = new QDockWidget(tr("DockWindow2"), this);
    dock1->setFeatures(QDockWidget::DockWidgetFloatable|QDockWidget::DockWidgetClosable);
    QTextEdit* text2 = new QTextEdit();
    text2->setText("Window2");
    dock2->setWidget(text2);
    this->addDockWidget(Qt::LeftDockWidgetArea, dock2);

    // 创建停靠窗口3
    QDockWidget* dock3 = new QDockWidget(tr("DockWindow3"), this);
    dock3->setFeatures(QDockWidget::AllDockWidgetFeatures);
    QTextEdit* text3 = new QTextEdit();
    text3->setText("Window3");
    dock3->setWidget(text3);
    this->addDockWidget(Qt::LeftDockWidgetArea, dock3);
}

QDockWidgetDemo::~QDockWidgetDemo()
{

}
