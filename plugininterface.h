#ifndef PLUGININTERFACE_H
#define PLUGININTERFACE_H

#include <QObject>
#include <QString>
#include <QPixmap>

#include <virtualkey.h>

class PluginInterface
{
public:
    virtual ~PluginInterface(){}

    virtual QString pluginName() = 0;
    virtual quint16 getPluginsNumber() = 0;
    virtual VirtualKey* getpluginChildPtr(quint16 number) = 0;
    virtual QString getpluginChildName(quint16 number) = 0;

signals:
    void sendData(QByteArray);

};

QT_BEGIN_NAMESPACE

#define Interface_iid "HadesPlugin.Interface"
Q_DECLARE_INTERFACE(PluginInterface, Interface_iid)

QT_END_NAMESPACE

#endif // PLUGININTERFACE_H
