#ifndef SPINBOXDELEGATE_H
#define SPINBOXDELEGATE_H
#include <QItemDelegate>
#include <QSpinBox>

/**
 * @brief The SpinBoxDelegate class
 * SpinBox委托类，限制输入1-100的int数
 */
class SpinBoxDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    SpinBoxDelegate(QObject *parent = nullptr)
        : QItemDelegate(parent) { }

    QWidget *createEditor(QWidget *parent,
                          const QStyleOptionViewItem &option,
                          const QModelIndex &index) const override
    {
        QSpinBox *editor = new QSpinBox(parent);
        editor->setMinimum(1);
        editor->setMaximum(100);
        return editor;
    }

    void setEditorData(QWidget *editor, const QModelIndex &index) const override
    {
        int value = index.model()->data(index, Qt::EditRole).toInt();
        QSpinBox *spinBox = static_cast<QSpinBox*>(editor);
        spinBox->setValue(value);
    }

    void setModelData(QWidget *editor,
                      QAbstractItemModel *model,
                      const QModelIndex &index) const override
    {
        QSpinBox *spinBox = static_cast<QSpinBox*>(editor);
        spinBox->interpretText();
        int value = spinBox->value();
        model->setData(index, value, Qt::EditRole);
    }

    void updateEditorGeometry(QWidget *editor,
                              const QStyleOptionViewItem &option,
                              const QModelIndex &index) const override
    {
        editor->setGeometry(option.rect);
    }
};

#endif // SPINBOXDELEGATE_H
