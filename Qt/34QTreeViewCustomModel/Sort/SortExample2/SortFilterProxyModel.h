#ifndef SORTFILTERPROXYMODEL_H
#define SORTFILTERPROXYMODEL_H

#include <QSortFilterProxyModel>

class SortFilterProxyModel : public QSortFilterProxyModel
{
public:
    SortFilterProxyModel(QObject *parent = nullptr);

protected:
    virtual bool lessThan(const QModelIndex &left, const QModelIndex &right) const;
};

#endif // SORTFILTERPROXYMODEL_H
