#ifndef READONLYDELEGATE_H
#define READONLYDELEGATE_H
#include <QItemDelegate>

class ReadOnlyDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    ReadOnlyDelegate(QObject *parent = nullptr)
        : QItemDelegate(parent) { }

    QWidget *createEditor(QWidget* parent,
                          const QStyleOptionViewItem &option,
                          const  QModelIndex &index) const
    { return nullptr; }
};

#endif // READONLYDELEGATE_H
