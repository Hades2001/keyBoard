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

private:

};

#endif // SYSTOOLS_H
