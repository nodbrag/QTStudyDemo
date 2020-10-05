#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QToolButton>
#include <QApplication>
#include <QStyle>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QToolButton *toolButton = new QToolButton(this);
    toolButton->setIcon( QApplication::style()->standardIcon(QStyle::SP_ComputerIcon) );
    toolButton->setToolButtonStyle( Qt::ToolButtonTextUnderIcon);
    toolButton->setFixedSize(toolButton->iconSize().width() + 20, toolButton->iconSize().height() + 10);
    toolButton->setPopupMode(QToolButton::InstantPopup);

    QMenu *menu = new QMenu();
    menu->addAction(QApplication::style()->standardIcon(QStyle::SP_MessageBoxCritical), tr("图标视图"));
    menu->addAction(QApplication::style()->standardIcon(QStyle::SP_MessageBoxQuestion), tr("细节视图"));

    toolButton->setMenu(menu);
}

MainWindow::~MainWindow()
{
    delete ui;
}

