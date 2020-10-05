#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTreeView>
#include <QHeaderView>
#include <QFile>
#include "TreeModel.h"
#include "TreeItem.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    treeView = new QTreeView(ui->widget);
    treeView->setSelectionBehavior(QTreeView::SelectRows);			//一次选中整行
    treeView->setSelectionMode(QTreeView::SingleSelection);        //单选，配合上面的整行就是一次选单行
    treeView->setFocusPolicy(Qt::NoFocus);                         //去掉鼠标移到单元格上时的虚线框
    treeView->header()->setStretchLastSection(true);               //最后一列自适应宽度

    QHBoxLayout* h = new QHBoxLayout(ui->widget);
    h->addWidget(treeView);

    QVector<Province*> proList = initData();
    setModel(proList);
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

void MainWindow::on_pushButton1_clicked()
{
    loadQssFile(":/res/style1.qss");
}

void MainWindow::on_pushButton2_clicked()
{
    loadQssFile(":/res/style2.qss");
}

void MainWindow::on_pushButton3_clicked()
{
    loadQssFile(":/res/style3.qss");
}

void MainWindow::loadQssFile(const QString &qss)
{
    QFile file(qss);
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qApp->setStyleSheet(file.readAll());
        file.close();
    }
}


