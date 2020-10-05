#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}
class Executor;
class IRunable;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_start_clicked();

    void on_pushButton_pause_clicked();

    void on_pushButton_stop_clicked();

    void on_pushButton_resume_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    Executor* executor;
    QList<IRunable*> runableList;
};

#endif // MAINWINDOW_H
