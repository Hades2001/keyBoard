#ifndef PULGINMAP_H
#define PULGINMAP_H

#include <QObject>
#include <QMap>
#include <QDebug>
#include "plugininterface.h"
#include "imagemap.h"
#include "virtualkey.h"

class pluginMap
{
public:
    pluginMap();
    ~pluginMap();
    QMap <QString, PluginInterface *> Map;
    void Register(QString,PluginInterface *);
};

extern pluginMap uPluginMap;

#endif // PULGINMAP_H
