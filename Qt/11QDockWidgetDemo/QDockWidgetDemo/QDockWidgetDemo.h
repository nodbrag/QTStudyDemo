#ifndef QDOCKWIDGETDEMO_H
#define QDOCKWIDGETDEMO_H

#include <QMainWindow>

class QTextEdit;

class QDockWidgetDemo : public QMainWindow
{
    Q_OBJECT

public:
    QDockWidgetDemo(QWidget *parent = 0);
    ~QDockWidgetDemo();

private:
    QTextEdit* mainTextEdit;
};

#endif // QDOCKWIDGETDEMO_H
