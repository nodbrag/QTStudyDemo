#ifndef APPLICATIONSETTING_H
#define APPLICATIONSETTING_H

#include <QString>
#include <QVariant>

class QSettings;

class ApplicationSetting
{
public:
    ApplicationSetting();
    ~ApplicationSetting();

    void setValue(const QString &key, const QVariant &value);
    QVariant value(const QString &key, const QVariant &defaultValue = QVariant()) const;

private:
    QSettings* setting;
};

#endif // APPLICATIONSETTING_H
