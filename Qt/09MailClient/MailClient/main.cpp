#include "MailClient.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MailClient w;
    w.show();

    return a.exec();
}
