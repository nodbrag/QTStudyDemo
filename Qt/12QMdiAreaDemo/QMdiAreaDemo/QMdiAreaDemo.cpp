#include "QMdiAreaDemo.h"
#include <QtWidgets>

QMdiAreaDemo::QMdiAreaDemo(QWidget *parent)
    : QMainWindow(parent)
{
    // 创建操作控件
    QPushButton* previousBtn = new QPushButton("上一个窗体");
    QPushButton* nextBtn = new QPushButton("下一个窗体");
    QPushButton* closeBtn = new QPushButton("关闭当前窗体");
    QPushButton* closeAllBtn = new QPushButton("关闭所有窗体");

    QVBoxLayout* groupLayout = new QVBoxLayout(); // group内布局
    groupLayout->addWidget(previousBtn);
    groupLayout->addWidget(nextBtn);
    groupLayout->addWidget(closeBtn);
    groupLayout->addWidget(closeAllBtn);

    QGroupBox* groupBox = new QGroupBox("操作");
    groupBox->setLayout(groupLayout);

    // 创建子窗口
    QTextEdit* window1 = new QTextEdit();
    window1->setHtml("C");
    QTextEdit* window2 = new QTextEdit();
    window2->setHtml("C++");
    QTextEdit* window3 = new QTextEdit();
    window3->setHtml("Java");
    QTextEdit* window4 = new QTextEdit();
    window4->setHtml("New Window!");

    // 创建多文档显示控件
    mdiArea = new QMdiArea();
    mdiArea->addSubWindow(window1);
    mdiArea->addSubWindow(window2);
    mdiArea->addSubWindow(window3);
    mdiArea->addSubWindow(window4);
    mdiArea->cascadeSubWindows(); // 层叠式子窗口

    QHBoxLayout* mainLayout = new QHBoxLayout(); // 主界面布局
    mainLayout->addWidget(mdiArea);
    mainLayout->addWidget(groupBox);

    // 创建中心窗口部件
    QWidget* centraWidget = new QWidget();
    centraWidget->setLayout(mainLayout);
    setCentralWidget(centraWidget);

    // 创建信号槽
    connect(previousBtn, SIGNAL(clicked()), this, SLOT(on_PreviousBtn_Clicked()));
    connect(nextBtn, SIGNAL(clicked()), this, SLOT(on_NextBtn_Clicked()));
    connect(closeBtn, SIGNAL(clicked()), this, SLOT(on_CloseBtn_Clicked()));
    connect(closeAllBtn, SIGNAL(clicked()), this, SLOT(on_CloseAllBtn_Clicked()));
}

QMdiAreaDemo::~QMdiAreaDemo()
{

}

void QMdiAreaDemo::on_PreviousBtn_Clicked()
{
    mdiArea->activatePreviousSubWindow();
}

void QMdiAreaDemo::on_NextBtn_Clicked()
{
    mdiArea->activateNextSubWindow();
}

void QMdiAreaDemo::on_CloseBtn_Clicked()
{
    mdiArea->closeActiveSubWindow();
}

void QMdiAreaDemo::on_CloseAllBtn_Clicked()
{
    mdiArea->closeAllSubWindows();
}
