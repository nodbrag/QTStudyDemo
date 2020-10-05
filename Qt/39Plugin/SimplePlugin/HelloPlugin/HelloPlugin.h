#ifndef HELLOPLUGIN_H
#define HELLOPLUGIN_H

#include "HelloInterface.h"

class HelloPlugin : public HelloInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID HelloPluginInterface_iid FILE "HelloPlugin.json")
public:
    explicit HelloPlugin(QObject *parent = nullptr);

    virtual void func() override;

protected:
    virtual void setData(const QString& data) override;
};

#endif // HELLOPLUGIN_H
