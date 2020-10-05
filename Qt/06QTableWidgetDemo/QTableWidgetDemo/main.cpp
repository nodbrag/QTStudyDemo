#include "QTableWidgetDemo.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTableWidgetDemo w;
    w.show();

    return a.exec();
}
