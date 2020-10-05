#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QHBoxLayout>
#include "TextListWidget.h"

const QString str = QStringLiteral("静夜思\n \
                                   ----------------------------\n \
                                   床前明月光，疑是地上霜。 \n \
                                   举头望明月，低头思故乡。");

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    listWidget = new TextListWidget(ui->widget);
    QHBoxLayout* layout = new QHBoxLayout(ui->widget);
    layout->addWidget(listWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    listWidget->addItem(str);
}
