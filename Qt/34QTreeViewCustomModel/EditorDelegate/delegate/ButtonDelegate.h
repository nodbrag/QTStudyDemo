#ifndef BUTTONDELEGATE_H
#define BUTTONDELEGATE_H
#include "PersistentStyledItemDelegate.h"
#include <QPushButton>
#include <QHBoxLayout>

/**
 * @brief The ButtonDelegate class
 * Button委托类
 */
class ButtonDelegate : public PersistentStyledItemDelegate
{
    Q_OBJECT
public:
    ButtonDelegate(QObject *parent = nullptr)
        : PersistentStyledItemDelegate(parent) { }

    void setText(const QString &text) { _text = text; }
    void setIcon(const QIcon &icon) { _icon = icon; }

signals:
    void clicked(const QModelIndex& index);

public:
    //因为按钮既不需要从model读取数据，也不需要写入，因此仅需要重写一个函数即可
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
    {
        QPersistentModelIndex perIndex(index);

        QWidget *widget = new QWidget(parent);
        widget->setAutoFillBackground(true);
        QHBoxLayout *layout = new QHBoxLayout();
        layout->addStretch();
        layout->setContentsMargins(2, 2, 2, 2);

        QPushButton *btn = new QPushButton();
        btn->setMinimumHeight(24);
        btn->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        if (!_text.isEmpty())   btn->setText(_text);
        if (!_icon.isNull())   btn->setIcon(_icon);
        btn->setStyleSheet(BTN_QSS);
        layout->addWidget(btn);
        layout->addStretch();
        widget->setLayout(layout);

        QObject::connect(btn,&QPushButton::clicked,[=]{
            QModelIndex tIndex = static_cast<QModelIndex>(perIndex);
            //const成员里，不能修改对象，因此不能emit信号
            auto temp = const_cast<ButtonDelegate *>(this);
            emit temp->clicked(tIndex);
        });

        return widget;
    }

private:
    QString _text;
    QIcon _icon;
    const QString BTN_QSS = "QPushButton{"
                                "border-image: url(:/res/download_normal.png);"
                            "}"
                            "QPushButton::hover{"
                               "border-image: url(:/res/download_normal.png);"
                            "}"
                            "QPushButton::pressed{"
                                "border-image: url(:/res/download_press.png);"
                            "}";
};

#endif // BUTTONDELEGATE_H
