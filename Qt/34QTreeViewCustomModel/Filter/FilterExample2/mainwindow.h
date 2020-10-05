#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "TreeFilterProxyModel.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_lineEdit_textChanged(const QString &text);

    void on_spinBox_valueChanged(int arg1);

    void on_spinBox_2_valueChanged(int arg1);

    void on_comboBox_2_currentIndexChanged(int index);

private:
    void initData();

private:
    Ui::MainWindow *ui;
    TreeFilterProxyModel* proxyModel;
};

#endif // MAINWINDOW_H
