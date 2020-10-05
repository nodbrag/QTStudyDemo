#include <QApplication>
#include "LoginDialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    LoginDialog dialog;
    dialog.show();

    return a.exec();
}
