#ifndef COMBOBOXDELEGATE_H
#define COMBOBOXDELEGATE_H
#include <QItemDelegate>
#include <QComboBox>

/**
 * @brief The ComboBoxDelegate class
 * ComboBox委托类
 */
class ComboBoxDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    ComboBoxDelegate(QObject *parent = nullptr)
        : QItemDelegate(parent) { }

    void setItems(const QStringList &texts) { _texts = texts; }

public:
    QWidget *createEditor(QWidget *parent,
                          const QStyleOptionViewItem &option,
                          const QModelIndex &index) const override
    {
        QComboBox *editor = new QComboBox(parent);
        editor->addItems(_texts);
        return editor;
    }

    void setEditorData(QWidget *editor, const QModelIndex &index) const override
    {
        QString text = index.model()->data(index, Qt::EditRole).toString();
        QComboBox *comboBox = static_cast<QComboBox*>(editor);
        int tindex = comboBox->findText(text);
        comboBox->setCurrentIndex(tindex);
    }

    void setModelData(QWidget *editor,
                      QAbstractItemModel *model,
                      const QModelIndex &index) const override
    {
        QComboBox *comboBox = static_cast<QComboBox*>(editor);
        QString text = comboBox->currentText();
        model->setData(index, text, Qt::EditRole);
    }

    void updateEditorGeometry(QWidget *editor,
                               const QStyleOptionViewItem &option,
                               const QModelIndex &index) const override
    {
        editor->setGeometry(option.rect);
    }

private:
    QStringList _texts;
};

#endif // COMBOBOXDELEGATE_H
