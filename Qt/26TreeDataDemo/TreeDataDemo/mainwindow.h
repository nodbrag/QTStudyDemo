#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class Node;
class Menu;
class QTreeWidgetItem;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void slot_customContextMenuRequested(const QPoint &pos);
    void slot_update();

private:
    // 创建右键菜单
    void createRightMenu();

    // 递归方式实现向QTreeWidget添加数据
    void addDataToTreeWidget_Recursion(Node* root);

    // 迭代方式实现向QTreeWidget添加数据
    void addDataToTreeWidget_Iteration(Node* root);

    // 递归创建节点
    void createNode(QTreeWidgetItem* parent, Node* node);

    // 创建测试树形数据
    Node* createTestData();

private:
    Ui::MainWindow *ui;

    // 右键菜单
    QMenu*    _rightMenu;

    // 测试数据
    Node*    _root;
};

#endif // MAINWINDOW_H
