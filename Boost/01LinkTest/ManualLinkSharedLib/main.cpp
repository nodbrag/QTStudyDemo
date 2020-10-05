#include <QCoreApplication>
#include <boost/thread.hpp>
#include <QDebug>

void hello()
{
    qDebug() << "Hello world, I'm a thread!";
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    boost::thread thrd(&hello);
    thrd.join();

    return a.exec();
}
