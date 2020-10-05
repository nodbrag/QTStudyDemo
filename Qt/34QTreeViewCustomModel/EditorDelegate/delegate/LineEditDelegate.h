#ifndef LINEEDITDELEGATE_H
#define LINEEDITDELEGATE_H
#include <QItemDelegate>
#include <QLineEdit>
#include <QIntValidator>

/**
 * @brief The LineEditDelegate class
 * LineEdit委托类，限制只允许int输入
 */
class LineEditDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    LineEditDelegate(QObject *parent = nullptr)
        : QItemDelegate(parent) { }

    QWidget *createEditor(QWidget *parent,
                          const QStyleOptionViewItem &option,
                          const QModelIndex &index) const override
    {
        QLineEdit *editor = new QLineEdit(parent);
        editor->setValidator(new QIntValidator(parent));
        return editor;
    }

    void setEditorData(QWidget *editor, const QModelIndex &index) const override
    {
        QString text = index.model()->data(index, Qt::EditRole).toString();
        QLineEdit *lineEdit = static_cast<QLineEdit*>(editor);
        lineEdit->setText(text);
    }

    void setModelData(QWidget *editor,
                      QAbstractItemModel *model,
                      const QModelIndex &index) const override
    {
        QLineEdit *lineEdit = static_cast<QLineEdit*>(editor);
        QString text = lineEdit->text();
        model->setData(index, text, Qt::EditRole);
    }

    void updateEditorGeometry(QWidget *editor,
                              const QStyleOptionViewItem &option,
                              const QModelIndex &index) const override
    {
        editor->setGeometry(option.rect);
    }
};

#endif // LINEEDITDELEGATE_H
