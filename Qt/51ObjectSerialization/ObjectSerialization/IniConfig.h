#ifndef INICONFIG_H
#define INICONFIG_H

#include <QByteArray>

class IAlgo;
class QSettings;

class IniConfig
{
public:
    IniConfig();
    ~IniConfig();

    void setAlgos(const QList<IAlgo*>& algos);
    QList<IAlgo*> getAlgos() const;

private:
    QSettings* setting;
};

#endif // INICONFIG_H
