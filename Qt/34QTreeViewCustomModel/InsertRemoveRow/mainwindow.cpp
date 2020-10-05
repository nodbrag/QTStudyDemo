#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTreeView>
#include <QHeaderView>
#include <QStyle>
#include <QMessageBox>
#include "TreeModel.h"
#include "TreeItem.h"

#pragma execution_character_set("utf-8")

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    treeView = new QTreeView(this);
    treeView->setSelectionBehavior(QTreeView::SelectRows);			//一次选中整行
    treeView->setSelectionMode(QTreeView::SingleSelection);        //单选，配合上面的整行就是一次选单行
    treeView->setFocusPolicy(Qt::NoFocus);                         //去掉鼠标移到单元格上时的虚线框
    treeView->header()->setStretchLastSection(true);               //最后一列自适应宽度
    setCentralWidget(treeView);

    QVector<Province*> proList = initData();
    setModel(proList);

    // 为treeView添加右键菜单
    treeView->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(treeView, &QTreeView::customContextMenuRequested, this, &MainWindow::onTreeViewMenuRequested);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QVector<Province*> MainWindow::initData()
{
    // 初始化数据，5个省，每个省5人
    QVector<Province*> proList;
    int provinceCount = 5;
    int personCount = 5;
    for(int i = 0; i < provinceCount; i++)
    {
        Province* pro = new Province();
        pro->name = QString("Province%1").arg(i);
        for(int j = 0; j < personCount; j++)
        {
            Person* per = new Person();
            per->name = QString("name%1").arg(j);
            per->sex = "man";
            per->age = 25;
            per->phone = "123456789";
            pro->people.append(per);
        }
        proList.append(pro);
    }
    return proList;
}

void MainWindow::setModel(const QVector<Province *> &proList)
{
    QStringList headers;
    headers << QString("名称/姓名")
            << QString("性别")
            << QString("年龄")
            << QString("电话");

    TreeModel* model = new TreeModel(headers, treeView);
    TreeItem* root = model->root();
    foreach (auto pro, proList)
    {
        TreeItem* province = new TreeItem(root);
        province->setPtr(pro); // 保存数据指针
        province->setType(TreeItem::PROVINCE); // 设置节点类型为PROVINCE
        root->addChild(province);

        foreach (auto per, pro->people)
        {
            TreeItem* person = new TreeItem(province);
            person->setPtr(per);    // 保存数据指针
            person->setType(TreeItem::PERSON);  // 设置节点类型为PERSON
            province->addChild(person);
        }
    }

    treeView->setModel(model);
}

void MainWindow::onTreeViewMenuRequested(const QPoint &pos)
{
    QModelIndex curIndex = treeView->indexAt(pos);
    if (curIndex.isValid()) // 右键选中了有效index
    {
        QIcon view = QApplication::style()->standardIcon(QStyle::SP_MessageBoxInformation);
        QIcon test = QApplication::style()->standardIcon(QStyle::SP_DesktopIcon);

        // 创建菜单
        QMenu menu;
        menu.addAction(view, QString("添加一行"), this, &MainWindow::onActionInsert);
        menu.addSeparator();
        menu.addAction(test, QString("删除一行"), this, &MainWindow::onActionRemove);
        menu.exec(QCursor::pos());
    }
}

void MainWindow::onActionInsert()
{
    QModelIndex index = treeView->currentIndex();
    if(index.isValid())
    {
        treeView->model()->insertRow(index.row(), index.parent());
    }
}

void MainWindow::onActionRemove()
{
    QModelIndex index = treeView->currentIndex();
    if(index.isValid())
    {
        treeView->model()->removeRow(index.row(), index.parent());
    }
}
