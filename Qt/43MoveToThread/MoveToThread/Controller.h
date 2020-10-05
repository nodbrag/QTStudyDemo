#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <QThread>

class Controller : public QObject
{
    Q_OBJECT
public:
    Controller(QObject* parent = nullptr);
    ~Controller();

public slots:
    void handleResults(const QString &des);

signals:
    void operate(const QString &cmd);

private:
    QThread thread;
};

#endif // CONTROLLER_H
