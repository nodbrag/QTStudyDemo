#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QStandardItemModel>
#include <QMessageBox>
#include "ReadOnlyDelegate.h"
#include "LineEditDelegate.h"
#include "SpinBoxDelegate.h"
#include "ComboBoxDelegate.h"
#include "ProgressBarDelegate.h"
#include "IconDelegate.h"
#include "DateTimeEditDelegate.h"
#include "ButtonDelegate.h"

static const QString ProgressBar_QssStr =  "QProgressBar{"
                                           "    border:none;"
                                           "    background:rgb(210, 225, 240);"
                                           "    border-radius:4px;"
                                           "    text-align:center;"
                                           "}"
                                           "QProgressBar::chunk {"
                                           "    background:rgb(60, 140, 220);"
                                           "    border-radius:4px;"
                                           "}";

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initData();

    ReadOnlyDelegate* readOnly = new ReadOnlyDelegate(ui->treeView);
    LineEditDelegate* lineEdit = new LineEditDelegate(ui->treeView);
    SpinBoxDelegate* spinBox = new SpinBoxDelegate(ui->treeView);
    ComboBoxDelegate* comboBox = new ComboBoxDelegate(ui->treeView);
    comboBox->setItems(QStringList()<<"支出"<<"收入");
    ProgressBarDelegate* progressBar = new ProgressBarDelegate(ui->treeView);
    IconDelegate* icon = new IconDelegate(ui->treeView);
    DateTimeEditDelegate* dateTime = new DateTimeEditDelegate(ui->treeView);
    ButtonDelegate* button = new ButtonDelegate(ui->treeView);
    connect(button, &ButtonDelegate::clicked, this, &MainWindow::onButtonClicked);

    ui->treeView->setItemDelegateForColumn(0, readOnly);
    ui->treeView->setItemDelegateForColumn(1, lineEdit);
    ui->treeView->setItemDelegateForColumn(2, spinBox);
    ui->treeView->setItemDelegateForColumn(3, comboBox);
    ui->treeView->setItemDelegateForColumn(4, progressBar);
    ui->treeView->setItemDelegateForColumn(5, icon);
    ui->treeView->setItemDelegateForColumn(6, dateTime);
    ui->treeView->setItemDelegateForColumn(7, button);

    qApp->setStyleSheet(ProgressBar_QssStr);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// 序号(只读)，单号(lineEdit)，金额(QSpinBox)，类型(QComboBox支出/收入),进度(进度条+100%),状态(图片)，时间,操作(按钮)
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
         QStandardItem *item3 = new QStandardItem("25");
         QStandardItem *item4 = new QStandardItem("支出");
         QStandardItem *item5 = new QStandardItem("80");
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
    ui->treeView->setModel(model);
    ui->treeView->setStyleSheet("QTreeView::item {"
                                "height: 40px;"
                                "}");
}

void MainWindow::onButtonClicked(const QModelIndex &index)
{
    if(!index.isValid())
            return;

    QMessageBox::information(this, "提示", QString("点击(%1,%2)").arg(index.row()).arg(index.column()));
}
