#ifndef SYSTOOLS_H
#define SYSTOOLS_H

#include "plugininterface.h"

#include "keytimer.h"

class sysTools : public PluginInterface
{
public:
    sysTools(QObject *parent = nullptr);
    QString pluginName(){ return QString("SystemTools");}
    quint16 getPluginsNumber(){ return quint16(syskeyList.size());}
    VirtualKey* getpluginChildPtr(quint16 number);

private:
    QList<VirtualKey> syskeyList;
};

#endif // SYSTOOLS_H
