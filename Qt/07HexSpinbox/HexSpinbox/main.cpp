/*
 * 自定义16进制微调框控件
*/

#include "HexSpinbox.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    HexSpinbox w;
    w.show();

    return a.exec();
}
