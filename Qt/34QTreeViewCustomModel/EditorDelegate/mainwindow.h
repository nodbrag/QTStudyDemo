#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QModelIndex>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void initData();

private slots:
    void onButtonClicked(const QModelIndex& index);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
