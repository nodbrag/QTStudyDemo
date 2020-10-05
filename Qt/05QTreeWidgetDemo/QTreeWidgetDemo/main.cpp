#include "QtreeWidgetDemo.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTreeWidgetDemo w;
    w.show();

    return a.exec();
}
