#include "TextListWidget.h"
#include "TextItemWidget.h"

#define LIST_ITEM_USER_ROLE   (Qt::UserRole + 0x01)

TextListWidget::TextListWidget(QWidget *parent)
    :QListWidget (parent)
{

}

void TextListWidget::addItem(const QString &text, const QVariant &userData)
{
    TextItemWidget* widget = new TextItemWidget();
    widget->setText(text);
    connect(widget, &TextItemWidget::deleteBtnClicked, this, &TextListWidget::onBtnClicked);

    QListWidgetItem* item = new QListWidgetItem();
    item->setData(LIST_ITEM_USER_ROLE, userData);
    QListWidget::addItem(item);
    QListWidget::setItemWidget(item, widget); // 必须先addItem，后才能setItemWidget
    item->setSizeHint(widget->size());

    widgetItemMap[widget] = item;
}

QVariant TextListWidget::userData(int row)
{
    return item(row)->data(LIST_ITEM_USER_ROLE);
}

void TextListWidget::onBtnClicked()
{
    QObject* widget = sender();
    QListWidgetItem* item = widgetItemMap[widget];
    delete item;
    delete widget;
    widgetItemMap.remove(widget);
}
