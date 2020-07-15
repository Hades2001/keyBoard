#ifndef SYSTOOLS_H
#define SYSTOOLS_H

#include "plugininterface.h"

#include "key_mkdir.h"
#include "keytimer.h"
#include "keyexec.h"
#include "keydefine.h"
#include "keymultiopera.h"

class sysTools : public PluginInterface
{
public:
    sysTools(QObject *parent = nullptr);
    QString pluginName(){ return QString("SystemTools");}

private:

};

#endif // SYSTOOLS_H
