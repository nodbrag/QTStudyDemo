/*
 * 说明：button/QDateTimeEdit点击弹出tooltip；
*/

#include "QDateTimeEditTest.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QDateTimeEditTest w;
    w.show();

    return a.exec();
}
