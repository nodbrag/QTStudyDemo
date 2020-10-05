#ifndef QLISTWIDGETDEMO_H
#define QLISTWIDGETDEMO_H

#include <QDialog>

class QListWidget;
class QListWidgetItem;

class QListWidgetDemo : public QDialog
{
    Q_OBJECT

public:
    QListWidgetDemo(QWidget *parent = 0);
    ~QListWidgetDemo();

private slots:
    void on_listWidget_SelectionChanged();
    void on_listWidget_Clicked(QListWidgetItem* item);

private:
    QListWidget* listWidget;
};

#endif // QLISTWIDGETDEMO_H
