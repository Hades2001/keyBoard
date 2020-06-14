#ifndef PULGINMAP_H
#define PULGINMAP_H

#include <QObject>
#include <QMap>
#include "plugininterface.h"
#include "virtualkey.h"

class pulginMap
{
public:
    pulginMap();
    ~pulginMap();
    QMap <QString, PluginInterface *> Map;
};

extern pulginMap uPulginMap;

#endif // PULGINMAP_H
