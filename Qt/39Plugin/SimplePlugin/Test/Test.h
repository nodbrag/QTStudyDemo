#ifndef TEST_H
#define TEST_H
#include <QObject>
#include <QDebug>

class Test : public QObject
{
    Q_OBJECT
public slots:
    void recvFunc(const QString& str)
    {
        qDebug() << "Test received : " << str;
    }

signals:
    void sendFunc(const QString& str);
};

#endif // TEST_H
