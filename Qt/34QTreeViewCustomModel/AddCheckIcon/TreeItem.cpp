#include "TreeItem.h"
#include <QIcon>
#include "typedef.h"

TreeItem::TreeItem(TreeItem *parent)
    : _parent(parent),
      _type(UNKNOWN),
      _ptr(nullptr),
      _row(-1),
      _checked(false)
{

}

TreeItem::~TreeItem()
{
    removeChildren();
}

// 在本节点下添加子节点
void TreeItem::addChild(TreeItem *item)
{
    item->setRow(_children.size());
    _children.append(item);
}

// 清空所有子节点
void TreeItem::removeChildren()
{
    qDeleteAll(_children);
    _children.clear();
}

// 获取本节点第column列的数据
QVariant TreeItem::data(int column) const
{
    if(_type == PROVINCE) // 此节点是"省份"信息
    {
        if (column == COLUMN_NAME) // 省份，只有"name"字段，且显示在第一列
        {
            Province* p = (Province*)_ptr;
            return p->name;
        }
    }
    else if(_type == PERSON) // 此节点是"人口"信息
    {
        Person* p = (Person*)_ptr;
        switch (column)
        {
        case COLUMN_NAME:       return p->name;
        case COLUMN_SEX:        return p->sex;
        case COLUMN_AGE:        return QString::number(p->age);
        case COLUMN_PHONE:      return p->phone;
        default:                return QVariant();
        }
    }
    return QVariant();
}

bool TreeItem::checkable(int column) const
{
    if (column != COLUMN_NAME) // 除第一列外，其他列不允许勾选
    {
        return false;
    }
    if(_type == PERSON) // 第一列中只允许"人口"勾选
    {
        return true;
    }
    return false;
}

QVariant TreeItem::getIcon(int column)
{
    if (column != COLUMN_NAME)
        return QVariant();

    if(_type == PROVINCE)
    {
        return QIcon(":/res/province.png");
    }
    else if (_type == PERSON)
    {
        return QIcon(":/res/person.png");
    }
    return QVariant();
}
