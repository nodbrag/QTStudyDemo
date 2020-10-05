#ifndef QSCROLLAREADEMO_H
#define QSCROLLAREADEMO_H

#include <QMainWindow>

class QPushButton;
class QLabel;
class QScrollArea;
class QVBoxLayout;
class QGroupBox;

class QScrollAreaDemo : public QMainWindow
{
    Q_OBJECT

public:
    QScrollAreaDemo(QWidget *parent = 0);
    ~QScrollAreaDemo();

private slots:
    void on_OpenBtn_Clicked();

private:
    QPushButton* openBtn;
    QLabel* imageLabel;
    QScrollArea* scrollArea;
    QVBoxLayout* vLayout;
    QGroupBox* groupBox;
};

#endif // QSCROLLAREADEMO_H
