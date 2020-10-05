#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <QThread>

class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(QObject *parent = 0);
    ~Controller();

    void operate(const QString& para);

    void other();

signals:
    void signal_operate(const QString& para);
    void signal_other();

public slots:
    void slot_handleResults(int code);
    void slot_handleOtherRes();

private:
    QThread    _thread;

};

#endif // CONTROLLER_H
