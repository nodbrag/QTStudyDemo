/*
 * 说明：一个model数据显示于2个view上，演示程序
*/

#include <QApplication>
#include <QtWidgets>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSplitter* splitter = new QSplitter();
    QDirModel* model = new QDirModel();

    // 创建treeView
    QTreeView* tree = new QTreeView(splitter);
    tree->setModel(model);
    tree->setRootIndex(model->index(QDir::currentPath()));

    // 创建listView
    QListView* list = new QListView(splitter);
    list->setModel(model);
    list->setRootIndex(model->index(QDir::currentPath()));

    splitter->setWindowTitle("Two views onto the same directory model");
    splitter->show();

    return a.exec();
}
