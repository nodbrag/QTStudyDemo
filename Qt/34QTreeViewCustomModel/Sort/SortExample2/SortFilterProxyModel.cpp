#include "SortFilterProxyModel.h"
#include "typedef.h"
#include "TreeItem.h"

SortFilterProxyModel::SortFilterProxyModel(QObject *parent)
    : QSortFilterProxyModel(parent)
{

}

bool SortFilterProxyModel::lessThan(const QModelIndex &left, const QModelIndex &right) const
{
    TreeItem *item1 = static_cast<TreeItem*>(left.internalPointer());
    TreeItem *item2 = static_cast<TreeItem*>(right.internalPointer());
    if (left.column() == COLUMN_SEX && right.column() == COLUMN_SEX)
    {
        return TreeItem::lessThan_sex(item1, item2);
    }
    else if (left.column() == COLUMN_AGE && right.column() == COLUMN_AGE)
    {
        return TreeItem::lessThan_age(item1, item2);
    }
    return QSortFilterProxyModel::lessThan(left, right);
}
