#ifndef SYSTOOLS_H
#define SYSTOOLS_H

#include "plugininterface.h"

#include "key_mkdir.h"
#include "keytimer.h"

class sysTools : public PluginInterface
{
public:
    enum keyList{
        kMkdir = 0,
        kTimer,
        kTick,
        kMax,
    };
    sysTools(QObject *parent = nullptr);
    QString pluginName(){ return QString("SystemTools");}
    quint16 getPluginsNumber(){ return quint16(kMax);}
    VirtualKey* getpluginChildPtr(quint16 number);
    QString getpluginChildName(quint16 number);


private:
};

#endif // SYSTOOLS_H
