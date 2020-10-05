#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}
class ApplicationSetting;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void print(QObject* object);

    void testStructObject(ApplicationSetting* setting);
    void testNestedStructObject(ApplicationSetting* setting);
    void testStructObjectList(ApplicationSetting* setting);
    void testStructObjectTree(ApplicationSetting* setting);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
