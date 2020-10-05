#include "TreeItem.h"
#include "typedef.h"

TreeItem::TreeItem(TreeItem *parent)
    : _parent(parent),
      _type(UNKNOWN),
      _ptr(nullptr),
      _row(-1)
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

// item1的sex < item2的sex，则返回true
bool TreeItem::lessThan_sex(const TreeItem * item1, const TreeItem * item2)
{
    Person* left = static_cast<Person*>(item1->ptr());
    Person* right = static_cast<Person*>(item2->ptr());
    if (left->sex == "woman" && right->sex == "man") // 女士优先
    {
        return true;
    }
    return false;
}

// item1的age < item2的age，则返回true
bool TreeItem::lessThan_age(const TreeItem *item1, const TreeItem * item2)
{
    Person* left = static_cast<Person*>(item1->ptr());
    Person* right = static_cast<Person*>(item2->ptr());
    return (left->age < right->age);
}
