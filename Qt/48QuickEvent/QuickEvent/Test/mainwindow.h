#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDateTime>
#include "student.h"

namespace Ui {
class MainWindow;
}
class ChildDialog;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void event_show_time(const QDateTime &time);
    void event_student_event(const Student &stu);

private:
    Ui::MainWindow *ui;
    ChildDialog* childDialog;
};

#endif // MAINWINDOW_H
