#ifndef BASE_H
#define BASE_H

#include <QObject>

class Base : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int wid READ getWid WRITE setWid)
public:
    Base(QObject* parent=nullptr) :QObject(parent) {}

    virtual void func() = 0;

    int getWid() const { return _wid; }
    void setWid(int wid) { _wid = wid; }

private:
    int _wid;
};

#endif // BASE_H
