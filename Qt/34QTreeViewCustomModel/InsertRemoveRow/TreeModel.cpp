#include "TreeModel.h"
#include "TreeItem.h"

TreeModel::TreeModel(const QStringList& headers, QObject *parent)
    : QAbstractItemModel(parent)
{
    _headers = headers;
    _rootItem = new TreeItem();
}

TreeModel::~TreeModel()
{
    delete _rootItem;
}

TreeItem *TreeModel::itemFromIndex(const QModelIndex &index) const
{
    if (index.isValid())
    {
        TreeItem *item = static_cast<TreeItem*>(index.internalPointer());
        return item;
    }
    return _rootItem;
}

TreeItem *TreeModel::root()
{
    return _rootItem;
}

// 获取表头数据
QVariant TreeModel::headerData(int section, Qt::Orientation orientation,int role) const
{
    if (orientation == Qt::Horizontal)
    {
        if(role == Qt::DisplayRole)
        {
            return _headers.at(section);
        }
    }
    return QVariant();
}

// 获取index.row行，index.column列数据
QVariant TreeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    TreeItem *item = itemFromIndex(index);
    if (role == Qt::DisplayRole)
    {
        return item->data(index.column());
    }
    return QVariant();
}

// 在parent节点下，第row行，第column列位置上创建索引
QModelIndex TreeModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    TreeItem *parentItem = itemFromIndex(parent);
    TreeItem *item = parentItem->child(row);
    if (item)
        return createIndex(row, column, item);
    else
        return QModelIndex();
}

// 创建index的父索引
QModelIndex TreeModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    TreeItem *item = itemFromIndex(index);
    TreeItem *parentItem = item->parent();

    if (parentItem == _rootItem)
        return QModelIndex();
    return createIndex(parentItem->row(), 0, parentItem);
}

// 获取索引parent下有多少行
int TreeModel::rowCount(const QModelIndex &parent) const
{
    if (parent.column() > 0)
        return 0;

    TreeItem* item = itemFromIndex(parent);
    return item->childCount();
}

// 返回索引parent下有多少列
int TreeModel::columnCount(const QModelIndex &parent) const
{
    return _headers.size();
}

bool TreeModel::insertRows(int row, int count, const QModelIndex &parent)
{
    TreeItem *parentItem = itemFromIndex(parent);

    beginInsertRows(parent, row, row + count - 1);

    for (int i = 0; i < count; i++)
    {
        TreeItem* item = new TreeItem(parentItem);
        parentItem->insertChild(row + i, item);

        // 填充item数据
        if (parentItem->getType() == TreeItem::PROVINCE)
        {
            TreeItem::fillPersonData(item,
                                     QString("new name%1").arg(i),
                                     "man",
                                     25,
                                     "123456789");
        }
        else if (parentItem->getType() == TreeItem::UNKNOWN) // root
        {
            TreeItem::fillProvinceData(item, QString("new Province%1").arg(i));
        }
    }

    endInsertRows();
    return true;
}

bool TreeModel::removeRows(int row, int count, const QModelIndex &parent)
{
    TreeItem *parentItem = itemFromIndex(parent);

    beginRemoveRows(parent, row, row + count - 1);

    for (int i = 0; i < count; i++)
    {
        parentItem->removeChild(row);
    }

    endRemoveRows();
    return true;
}
