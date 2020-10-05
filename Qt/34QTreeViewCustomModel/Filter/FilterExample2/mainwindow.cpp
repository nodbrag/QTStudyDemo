#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QStandardItemModel>
#include <QDateTime>
#include <QRegExp>

#pragma execution_character_set("utf-8")

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initData();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initData()
{
    QString head = tr("分类/序号,单号,金额,类型,进度,状态S,时间,操作");
    QStandardItemModel* model = new QStandardItemModel();
    QStringList xx = head.split(',');
    model->setHorizontalHeaderLabels(head.split(","));

    QStandardItem *item = new QStandardItem("分类1");
    model->appendRow(item);
    int orderNo = 256159;
    for (int row = 0; row < 4; ++row) {
         QStandardItem *item1 = new QStandardItem(QString("%1").arg(row));
         QStandardItem *item2 = new QStandardItem(QString::number(orderNo + row));
         QStandardItem *item3 = new QStandardItem(QString::number(25+row));
         QStandardItem *item4 = new QStandardItem(row%2==0?"支出":"收入");
         QStandardItem *item5 = new QStandardItem(QString::number(80+row));
         QStandardItem *item6 = new QStandardItem("完成");
         QStandardItem *item7 = new QStandardItem(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
         QStandardItem *item8 = new QStandardItem("下载");
         QList<QStandardItem*> list;
         list << item1 << item2 << item3 << item4 << item5 << item6 << item7 << item8;
         item->appendRow(list);
    }

    ui->treeView->setSelectionBehavior(QTreeView::SelectRows);			//一次选中整行
    ui->treeView->setSelectionMode(QTreeView::SingleSelection);        //单选，配合上面的整行就是一次选单行
    ui->treeView->setFocusPolicy(Qt::NoFocus);                         //去掉鼠标移到单元格上时的虚线框
    ui->treeView->header()->setStretchLastSection(true);               //最后一列自适应宽度
    //ui->treeView->header()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->treeView->setStyleSheet("QTreeView::item {"
                                "height: 40px;"
                                "}");

    proxyModel = new TreeFilterProxyModel(this);
    proxyModel->setSourceModel(model);
    ui->treeView->setModel(proxyModel);

    ui->spinBox->setRange(0, 7);
    ui->spinBox->setValue(0);
    ui->spinBox_2->setRange(0, 7);
    ui->spinBox_2->setValue(7);

    ui->comboBox->addItem(tr("正则表达式"), QRegExp::RegExp);
    ui->comboBox->addItem(tr("通配符"), QRegExp::Wildcard);
    ui->comboBox->addItem(tr("固定字符串"), QRegExp::FixedString);

    ui->comboBox_2->addItem(tr("0列"));
    ui->comboBox_2->addItem(tr("1列"));
    ui->comboBox_2->addItem(tr("2列"));
    ui->comboBox_2->addItem(tr("3列"));
    ui->comboBox_2->addItem(tr("4列"));
    ui->comboBox_2->addItem(tr("5列"));
    ui->comboBox_2->addItem(tr("6列"));
    ui->comboBox_2->addItem(tr("7列"));
    ui->comboBox_2->addItem(tr("全部列"));
}

void MainWindow::on_lineEdit_textChanged(const QString &text)
{
    QRegExp::PatternSyntax syntax = QRegExp::PatternSyntax(ui->comboBox->currentData().toInt());
    QRegExp regExp(text, Qt::CaseInsensitive, syntax);
    proxyModel->setFilterRegExp(regExp);
}

void MainWindow::on_spinBox_valueChanged(int arg1)
{
    int begin = ui->spinBox->value();
    int end = ui->spinBox_2->value();
    proxyModel->setVisibleColumn(begin, end);

    on_lineEdit_textChanged(ui->lineEdit->text());
}

void MainWindow::on_spinBox_2_valueChanged(int arg1)
{
    on_spinBox_valueChanged(0);
}

void MainWindow::on_comboBox_2_currentIndexChanged(int index)
{
    if (index == 8)
        proxyModel->setFilterKeyColumn(-1);
    else
        proxyModel->setFilterKeyColumn(index);
}
