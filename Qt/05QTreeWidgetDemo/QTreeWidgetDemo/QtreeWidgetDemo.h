#ifndef QTREEWIDGETDEMO_H
#define QTREEWIDGETDEMO_H

#include <QDialog>

class QTreeWidget;
class QTreeWidgetItem;

class QTreeWidgetDemo : public QDialog
{
    Q_OBJECT

public:
    QTreeWidgetDemo(QWidget *parent = 0);
    ~QTreeWidgetDemo();

private slots:
    void on_TreeWidget_SelectionChanged();
    void on_TreeWidget_Clicked(QTreeWidgetItem* item, int column);

private:
    QTreeWidget* treeWidget;
};

#endif // QTREEWIDGETDEMO_H
