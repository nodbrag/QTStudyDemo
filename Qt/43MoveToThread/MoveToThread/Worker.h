#ifndef WORKER_H
#define WORKER_H

#include <QObject>

class Worker : public QObject
{
    Q_OBJECT
public:
    explicit Worker(QObject *parent = nullptr);
    ~Worker();

public slots:
    void doSomething(const QString& cmd);

signals:
    void resultNotify(const QString& des);
};

#endif // WORKER_H

