#ifndef QMIDAREADEMO_H
#define QMIDAREADEMO_H

#include <QMainWindow>

class QMdiArea;

class QMdiAreaDemo : public QMainWindow
{
    Q_OBJECT

public:
    QMdiAreaDemo(QWidget *parent = 0);
    ~QMdiAreaDemo();

private slots:
    void on_PreviousBtn_Clicked();
    void on_NextBtn_Clicked();
    void on_CloseBtn_Clicked();
    void on_CloseAllBtn_Clicked();

private:
    QMdiArea* mdiArea;
};

#endif // QMIDAREADEMO_H
