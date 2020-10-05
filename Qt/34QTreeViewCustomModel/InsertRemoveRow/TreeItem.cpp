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

void TreeItem::insertChild(int row, TreeItem* item)
{
    _children.insert(row, item);
}

void TreeItem::removeChild(int row)
{
    TreeItem *item = _children.at(row);
    delete item;
    _children.removeAt(row);
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

void TreeItem::fillPersonData(TreeItem *item, const QString& name, const QString& sex, int age, const QString& phone)
{
    Person* per = new Person();
    per->name = name;
    per->sex = sex;
    per->age = age;
    per->phone = phone;

    item->setPtr(per);    // 保存数据指针
    item->setType(TreeItem::PERSON);  // 设置节点类型为PERSON
}

void TreeItem::fillProvinceData(TreeItem *item, const QString &name)
{
    Province* pro = new Province();
    pro->name = name;

    item->setPtr(pro);    // 保存数据指针
    item->setType(TreeItem::PROVINCE);  // 设置节点类型为PROVINCE
}
