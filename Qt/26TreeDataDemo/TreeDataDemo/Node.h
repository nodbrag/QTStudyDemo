#ifndef NODE_H
#define NODE_H

#include <QString>
#include <vector>

// 树形数据结构类型
class QTreeWidget;
class QTreeWidgetItem;
class Node
{
public:
    Node(const QString& name="");
    virtual ~Node();

    // 设置/获取节点名称
    void setName(const QString& str) {_name = str;}
    QString getName()  {return _name;}

    // 添加/移除子节点
    bool addChild(Node* node);
    void removeChild(const Node* node);
    void removeAllChild();

    // 获取当前节点下所有子节点
    std::vector<Node*> children() {return _children;}

    // 使用当前节点作为根节点，创建一颗树
    void createTree(QTreeWidget* view);

    // 使用当前节点作为父节点，创建子节点
    void createTreeNode(QTreeWidgetItem* parent);

private:
    // 当前节点下是否存在此节点
    bool isExist(const Node* node);

private:
    // 节点名称
    QString    _name;

    // 子节点
    std::vector<Node*>     _children;
};

#endif // NODE_H
