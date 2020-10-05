#include "QListWidgetDemo.h"
#include <QtWidgets>

const char* iconPath = "://Resources/icon.png";

QListWidgetDemo::QListWidgetDemo(QWidget *parent)
    : QDialog(parent)
{
    // 创建list控件
    listWidget = new QListWidget(this);
    //listWidget->setViewMode(QListView::IconMode);

    // 创建list子成员
    QListWidgetItem* chromeItem = new QListWidgetItem();
    chromeItem->setIcon(QIcon(iconPath));
    chromeItem->setText(tr("Chrome"));

    QListWidgetItem* fireFoxItem = new QListWidgetItem();
    fireFoxItem->setIcon(QIcon(iconPath));
    fireFoxItem->setText(tr("Firefox"));

    QListWidgetItem* ieItem = new QListWidgetItem();
    ieItem->setIcon(QIcon(iconPath));
    ieItem->setText(tr("IE"));

    listWidget->addItem(chromeItem);
    listWidget->addItem(fireFoxItem);
    listWidget->addItem(ieItem);

    // 添加信号槽
    connect(listWidget, SIGNAL(itemSelectionChanged()), this, SLOT(on_listWidget_SelectionChanged()));
    connect(listWidget, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(on_listWidget_Clicked(QListWidgetItem*)));

    // 调整窗口大小
    this->setFixedSize(listWidget->sizeHint());
}

QListWidgetDemo::~QListWidgetDemo()
{

}

void QListWidgetDemo::on_listWidget_SelectionChanged()
{
    qDebug("list控件选择改变");
}


void QListWidgetDemo::on_listWidget_Clicked(QListWidgetItem* item)
{
    qDebug("list第%d项被点击", listWidget->row(item));
}
