#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMenu>
#include <QMessageBox>
#include <QTreeWidgetItem>
#include "Node.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 创建右键菜单
    createRightMenu();

    // 创建测试数据
    _root = createTestData();

    //addDataToTreeWidget_Recursion(root);  // 使用递归添加数据
    addDataToTreeWidget_Iteration(_root);   // 使用迭代添加数据
}

MainWindow::~MainWindow()
{
    delete _root;
    delete ui;
}

void MainWindow::slot_customContextMenuRequested(const QPoint & pos)
{
    _rightMenu->exec(QCursor::pos());
}

void MainWindow::slot_update()
{
    QMessageBox::warning(NULL, "提示", "刷新");
}

void MainWindow::createRightMenu()
{
    // 右键菜单
    _rightMenu = new QMenu(ui->treeWidget);
    QAction* updateAction = new QAction(QString("刷新"), ui->treeWidget);
    _rightMenu->addAction(updateAction);
    connect(updateAction, SIGNAL(triggered()), this, SLOT(slot_update()));

    ui->treeWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->treeWidget, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(slot_customContextMenuRequested(const QPoint &)));
}

void MainWindow::addDataToTreeWidget_Recursion(Node *root)
{
    // 创建根节点
    QTreeWidgetItem* rootItem = new QTreeWidgetItem(ui->treeWidget, QStringList(root->getName()));
    createNode(rootItem, root);
}

void MainWindow::addDataToTreeWidget_Iteration(Node* root)
{
    // 自动将树的数据填入树形控件中
    root->createTree(ui->treeWidget);
}

void MainWindow::createNode(QTreeWidgetItem* parent, Node *node)
{
    if(node)
    {
        std::vector<Node*> children = node->children();
        for(std::vector<Node*>::const_iterator it = children.begin(); it != children.end(); ++it)
        {
            QTreeWidgetItem* item = new QTreeWidgetItem(QStringList((*it)->getName()));
            parent->addChild(item);
            createNode(item, *it);
        }
    }
}

Node *MainWindow::createTestData()
{
    // 根节点
    Node* root = new Node("根");

    // 0
    Node* node = new Node("0");
    node->addChild(new Node("0-0"));
    node->addChild(new Node("0-1"));
    Node* temp = new Node("0-2");
    temp->addChild(new Node("0-2-0"));
    temp->addChild(new Node("0-2-1"));
    node->addChild(temp);
    root->addChild(node);

    // 1
    node = new Node("1");
    node->addChild(new Node("1-0"));
    temp = new Node("1-1");
    temp->addChild(new Node("1-1-0"));
    temp->addChild(new Node("1-1-1"));
    temp->addChild(new Node("1-1-2"));
    node->addChild(temp);
    node->addChild(new Node("1-2"));
    root->addChild(node);

    // 2
    node = new Node("2");
    root->addChild(node);
    return root;
}
