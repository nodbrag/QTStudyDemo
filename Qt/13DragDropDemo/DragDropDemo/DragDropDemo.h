#ifndef DRAGDROPDEMO_H
#define DRAGDROPDEMO_H

#include <QMainWindow>

class QTextEdit;

class DragDropDemo : public QMainWindow
{
    Q_OBJECT

public:
    DragDropDemo(QWidget *parent = 0);
    ~DragDropDemo();

protected:
    // 处理拖动事件
    void dragEnterEvent(QDragEnterEvent *event);
    // 处理放下事件
    void dropEvent(QDropEvent *event);

private:
    bool readFile(const QString& fileName);
    QTextEdit* textEdit;
};

#endif // DRAGDROPDEMO_H
