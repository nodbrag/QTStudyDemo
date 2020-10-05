#include "DragDropDemo.h"
#include <QtWidgets>

DragDropDemo::DragDropDemo(QWidget *parent)
    : QMainWindow(parent)
{
    textEdit = new QTextEdit();
    setCentralWidget(textEdit);

    // 设置允许接受拖放
    textEdit->setAcceptDrops(false);
    setAcceptDrops(true);

    setWindowTitle(tr("Text Editor"));
}

DragDropDemo::~DragDropDemo()
{

}

void DragDropDemo::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat("text/uri-list"))
    {
        event->acceptProposedAction(); // 允许在此窗口部件上拖放对象
    }
}

void DragDropDemo::dropEvent(QDropEvent *event)
{
    QList<QUrl> urls = event->mimeData()->urls();
    if (urls.isEmpty()) return;

    // 默认读取第一个拖放对象
    QString fileName = urls.first().toLocalFile();
    if (fileName.isEmpty())    return;

    if (readFile(fileName))
        setWindowTitle(tr("%1-%2").arg(fileName).arg(tr("Drag File")));
}

bool DragDropDemo::readFile(const QString& fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::warning(this,
                             tr("DragDropDemo"),
                             tr("无法读取%1:\n%2")
                             .arg(file.fileName())
                             .arg(file.errorString()));
        return false;
    }

    textEdit->setText("");
    while (!file.atEnd())
    {
        QString text = file.readLine();
        textEdit->append(text);
    }
    return true;
}
