#ifndef DATETIMEEDITDELEGATE_H
#define DATETIMEEDITDELEGATE_H
#include <QItemDelegate>
#include <QDateTimeEdit>

/**
 * @brief The DateTimeEditDelegate class
 * DateTimeEdit委托类
 */
class DateTimeEditDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    DateTimeEditDelegate(QObject *parent = nullptr)
        : QItemDelegate(parent) { }

    QWidget *createEditor(QWidget *parent,
                          const QStyleOptionViewItem &option,
                          const QModelIndex &index) const override
    {
        QDateTimeEdit *editor = new QDateTimeEdit(parent);
        return editor;
    }

    void setEditorData(QWidget *editor, const QModelIndex &index) const override
    {
        QDateTime time = index.model()->data(index, Qt::EditRole).toDateTime();
        QDateTimeEdit *dateTimeEdit = static_cast<QDateTimeEdit*>(editor);
        dateTimeEdit->setDateTime(time);
    }

    void setModelData(QWidget *editor,
                      QAbstractItemModel *model,
                      const QModelIndex &index) const override
    {
        QDateTimeEdit *dateTimeEdit = static_cast<QDateTimeEdit*>(editor);
        QString time = dateTimeEdit->dateTime().toString("yyyy-MM-dd hh:mm:ss");
        model->setData(index, time, Qt::EditRole);
    }

    void updateEditorGeometry(QWidget *editor,
                               const QStyleOptionViewItem &option,
                               const QModelIndex &index) const override
    {
        editor->setGeometry(option.rect);
    }
};

#endif // DATETIMEEDITDELEGATE_H
