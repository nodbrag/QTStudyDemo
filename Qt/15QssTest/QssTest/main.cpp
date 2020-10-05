/*
 * 说明：使用QSS修饰按钮控件演示程序。
*/

#include <QApplication>
#include <QFile>
#include <QPushButton>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QPushButton* btn = new QPushButton();
    btn->setObjectName("btn_Test");
    btn->resize(32, 32);
    btn->setCheckable(true);
    btn->show();

    QFile styleSheet(":/test.qss");
    if (!styleSheet.open(QIODevice::ReadOnly))
    {
        qWarning("Can't open the style sheet file.");
        return 0;
    }
    qApp->setStyleSheet(styleSheet.readAll());

    //btn->show();

    return a.exec();
}
