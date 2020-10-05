#include "ApplicationSetting.h"
#include <QSettings>
#include <QApplication>

ApplicationSetting::ApplicationSetting()
{
    setting = new QSettings(qApp->applicationDirPath() + "/setting.ini", QSettings::IniFormat);
}

ApplicationSetting::~ApplicationSetting()
{
    delete setting;
    setting = nullptr;
}

void ApplicationSetting::setValue(const QString &key, const QVariant &value)
{
    setting->setValue(key, value);
}

QVariant ApplicationSetting::value(const QString &key, const QVariant &defaultValue) const
{
    return setting->value(key, defaultValue);
}
