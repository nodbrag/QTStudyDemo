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

private slots:
    void on_pushButton1_clicked();
    void on_pushButton2_clicked();
    void on_pushButton3_clicked();

private:
    QVector<Province*> initData();
    void setModel(const QVector<Province*>& proList);
    void loadQssFile(const QString& qss);

private:
    Ui::MainWindow *ui;
    QTreeView* treeView;
};

#endif // MAINWINDOW_H
