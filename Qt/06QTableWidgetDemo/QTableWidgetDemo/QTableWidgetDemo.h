#ifndef QTABLEWIDGETDEMO_H
#define QTABLEWIDGETDEMO_H

#include <QDialog>

class QTableWidget;

class QTableWidgetDemo : public QDialog
{
    Q_OBJECT

public:
    QTableWidgetDemo(QWidget *parent = 0);
    ~QTableWidgetDemo();

private:
    QTableWidget* tableWidget;
};

#endif // QTABLEWIDGETDEMO_H
