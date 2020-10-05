#include "TreeFilterProxyModel.h"

TreeFilterProxyModel::TreeFilterProxyModel(QObject *parent)
    : QSortFilterProxyModel(parent),
      column_s(0),
      column_e(0)
{

}

bool TreeFilterProxyModel::filterAcceptsRow(int row, const QModelIndex &parent) const
{
    bool filter = QSortFilterProxyModel::filterAcceptsRow(row, parent);

    if (filter) // 若本来此节点就允许显示，则直接返回true。
    {
        return true;
    }
    else // 若此节点不允许显示，则需要判断此节点下面子节点是否有满足过滤条件的，若有，则需要显示此节点。
    {
        QModelIndex source_index = sourceModel()->index(row, 0, parent);
        for (int i = 0; i < sourceModel()->rowCount(source_index); i++)
        {
            if (filterAcceptsRow(i, source_index))
            {
                return true;
            }
        }
    }

    return false;
}

bool TreeFilterProxyModel::filterAcceptsColumn(int column, const QModelIndex &parent) const
{
    if (column_s == 0 && column_e == 0)
        return QSortFilterProxyModel::filterAcceptsColumn(column, parent);

    if (column < column_s || column > column_e)
        return false;
    return true;
}
