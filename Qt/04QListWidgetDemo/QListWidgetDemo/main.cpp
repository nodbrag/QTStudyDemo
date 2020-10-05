#include "QListWidgetDemo.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QListWidgetDemo w;
    w.show();

    return a.exec();
}
