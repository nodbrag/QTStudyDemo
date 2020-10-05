#ifndef TREEFILTERPROXYMODEL_H
#define TREEFILTERPROXYMODEL_H

#include <QSortFilterProxyModel>

class TreeFilterProxyModel : public QSortFilterProxyModel
{
public:
    TreeFilterProxyModel(QObject *parent = nullptr);

    void setVisibleColumn(int col_s, int col_e)
    {
        column_s = col_s;
        column_e = col_e;
    }

protected:
    virtual bool filterAcceptsRow(int row, const QModelIndex &parent) const override;
    virtual bool filterAcceptsColumn(int column, const QModelIndex &parent) const override;

private:
    int column_s;
    int column_e;
};

#endif // TREEFILTERPROXYMODEL_H
