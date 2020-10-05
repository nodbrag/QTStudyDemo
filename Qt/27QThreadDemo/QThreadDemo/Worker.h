#ifndef WORKER_H
#define WORKER_H

#include <QObject>

class Worker : public QObject
{
    Q_OBJECT
public:
    explicit Worker(QObject *parent = 0);

signals:
    void signal_result(int code);
    void signal_other();

public slots:
    void do_work(const QString& para);
    void do_other();

};

#endif // WORKER_H
