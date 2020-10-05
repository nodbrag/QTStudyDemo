#include <QApplication>
#include "TestForm.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TestForm w;
    w.show();

    return a.exec();
}
