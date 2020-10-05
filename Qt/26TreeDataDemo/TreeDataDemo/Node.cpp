#include "Node.h"
#include <algorithm>
#include <QTreeWidgetItem>

Node::Node(const QString &name)
    :_name(name)
{
}

Node::~Node()
{
    removeAllChild();
}

bool Node::addChild(Node *node)
{
    if (isExist(node))    return false;
    _children.push_back(node);
    return true;
}

void Node::removeChild(const Node *node)
{
    std::vector<Node*>::iterator result = find(_children.begin( ), _children.end( ), node); //查找node
    if (result == _children.end( )) //没找到
        return;
    delete (*result);
    _children.erase(result);
}

void Node::removeAllChild()
{
    std::vector<Node*>::iterator it = _children.begin();
    for (; it != _children.end(); it++)
    {
        delete (*it);
    }
    _children.clear();
}

void Node::createTree(QTreeWidget* view)
{
    QTreeWidgetItem* root = new QTreeWidgetItem(view, QStringList(_name));
    std::vector<Node*>::const_iterator it = _children.begin();
    for (; it != _children.end(); it++)
    {
        (*it)->createTreeNode(root);
    }
}

void Node::createTreeNode(QTreeWidgetItem* parent)
{
    QTreeWidgetItem* item = new QTreeWidgetItem(parent, QStringList(_name));
    std::vector<Node*>::const_iterator it = _children.begin();
    for (; it != _children.end(); it++)
    {
        (*it)->createTreeNode(item);
    }
}

bool Node::isExist(const Node *node)
{
    std::vector<Node*>::iterator result = find(_children.begin(), _children.end(), node); //查找node
    return (result != _children.end());
}
