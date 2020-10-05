#include "QTableWidgetDemo.h"
#include <QtWidgets>

QTableWidgetDemo::QTableWidgetDemo(QWidget *parent)
    : QDialog(parent)
{
    // 创建table控件
    tableWidget = new QTableWidget(this);
    tableWidget->setColumnCount(3);
    tableWidget->setRowCount(5);

    // 设置表头
    QStringList header;
    header << "ID" << "Name" << "Sex";
    tableWidget->setHorizontalHeaderLabels(header);

    // 设置表格
    tableWidget->setItem(0, 0, new QTableWidgetItem(QString("0001")));
    tableWidget->setItem(1, 0, new QTableWidgetItem(QString("0002")));
    tableWidget->setItem(2, 0, new QTableWidgetItem(QString("0003")));
    tableWidget->setItem(3, 0, new QTableWidgetItem(QString("0004")));
    tableWidget->setItem(4, 0, new QTableWidgetItem(QString("0005")));
    tableWidget->setItem(0, 1, new QTableWidgetItem(QString("20100112")));

    this->setFixedSize(tableWidget->sizeHint());
}

QTableWidgetDemo::~QTableWidgetDemo()
{

}
