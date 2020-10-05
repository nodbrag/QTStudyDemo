#include "QtreeWidgetDemo.h"
#include <QtWidgets>

QTreeWidgetDemo::QTreeWidgetDemo(QWidget *parent)
    : QDialog(parent)
{
    // 创建tree控件
    treeWidget = new QTreeWidget(this);
    //treeWidget->setColumnCount(1);
    treeWidget->setHeaderLabel(QString("Name"));

    // 创建根节点
    QTreeWidgetItem* root = new QTreeWidgetItem(treeWidget, QStringList(QString("Root")));
    new QTreeWidgetItem(root, QStringList(QString("Leaf 1")));
    QTreeWidgetItem* leaf2 = new QTreeWidgetItem(root, QStringList(QString("Leaf 2")));
    leaf2->setCheckState(0, Qt::Checked);

    this->setFixedSize(treeWidget->sizeHint());

    // 创建信号槽
    connect(treeWidget, SIGNAL(itemSelectionChanged()),
            this, SLOT(on_TreeWidget_SelectionChanged()));
    connect(treeWidget, SIGNAL(itemClicked(QTreeWidgetItem*,int)),
            this, SLOT(on_TreeWidget_Clicked(QTreeWidgetItem*,int)));
}

QTreeWidgetDemo::~QTreeWidgetDemo()
{

}

void QTreeWidgetDemo::on_TreeWidget_SelectionChanged()
{
    qDebug("tree控件选择发生改变");
}

void QTreeWidgetDemo::on_TreeWidget_Clicked(QTreeWidgetItem* item, int column)
{
    QString itemStr = item->text(column);
    qDebug("%s", itemStr.toStdString().c_str());
}
