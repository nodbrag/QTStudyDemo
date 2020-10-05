#ifndef PROGRESSBARDELEGATE_H
#define PROGRESSBARDELEGATE_H
#include <QItemDelegate>
#include <QProgressBar>
#include <QApplication>

/**
 * @brief The ProgressBarDelegate class
 * ProgressBar委托类
 */
class ProgressBarDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    ProgressBarDelegate(QObject *parent = nullptr)
        : QItemDelegate(parent) { }

    void paint(QPainter *painter,
               const QStyleOptionViewItem &option,
               const QModelIndex &index) const override
    {
        // 计算bar在表格中的位置
        int radio = 1;
        int top = option.rect.top() + radio;
        int left = option.rect.left() + radio;
        int width = option.rect.width() - 2 * radio;
        int height = option.rect.height() - 2 * radio;

        // 创建bar
        QStyleOptionProgressBar bar;
        bar.rect.setRect(left, top, width, height); // 设置bar位置
        bar.state = QStyle::State_Enabled;
        bar.progress = index.data(Qt::EditRole).toInt(); // 设置对应model列的值
        bar.minimum = 0;
        bar.maximum = 100;
        bar.textVisible = true;
        bar.text = QString("%1%").arg(bar.progress);
        bar.textAlignment = Qt::AlignCenter;

        QProgressBar pbar;
        QApplication::style()->drawControl(QStyle::CE_ProgressBar, &bar, painter, &pbar);
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

#endif // PROGRESSBARDELEGATE_H
