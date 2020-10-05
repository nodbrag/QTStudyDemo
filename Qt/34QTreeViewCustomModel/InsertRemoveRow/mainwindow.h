#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "typedef.h"

namespace Ui {
class MainWindow;
}
class QTreeView;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QVector<Province*> initData();
    void setModel(const QVector<Province*>& proList);

private slots:
    void onTreeViewMenuRequested(const QPoint &pos);
    void onActionInsert();
    void onActionRemove();

private:
    Ui::MainWindow *ui;
    QTreeView* treeView;
};

#endif // MAINWINDOW_H
