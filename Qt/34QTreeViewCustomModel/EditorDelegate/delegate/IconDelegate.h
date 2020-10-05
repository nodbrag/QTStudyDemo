#ifndef ICONDELEGATE_H
#define ICONDELEGATE_H
#include <QItemDelegate>
#include <QApplication>

/**
 * @brief The IconDelegate class
 * Icon委托类
 */
class IconDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    IconDelegate(QObject *parent = nullptr)
        : QItemDelegate(parent) { }

    void paint(QPainter *painter,
               const QStyleOptionViewItem &option,
               const QModelIndex &index) const override
    {
        QPixmap pixmap = QPixmap(":/res/complete.png");//.scaled(24, 24);
        qApp->style()->drawItemPixmap(painter, option.rect, Qt::AlignCenter, QPixmap(pixmap));
    }

    bool editorEvent(QEvent *event,
                     QAbstractItemModel *model,
                     const QStyleOptionViewItem &option,
                     const QModelIndex &index) override
    {
        if(event->type() == QEvent::MouseButtonDblClick) // 禁止双击编辑
            return true;
        return QItemDelegate::editorEvent(event,model,option,index);
    }
};

#endif // ICONDELEGATE_H
