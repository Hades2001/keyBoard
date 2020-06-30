#include "systools.h"

sysTools::sysTools(QObject *parent)
{
    Q_UNUSED(parent);   

}

VirtualKey* sysTools::getpluginChildPtr(quint16 number)
{
    VirtualKey* newVirtualKey = nullptr;
    switch( number )
    {
        case kMkdir : newVirtualKey = new key_mkdir;break;
        case kTimer : newVirtualKey = new KeyTimer;break;
        case kTick : newVirtualKey = new KeyTimer;break;
        default: newVirtualKey = nullptr; break;
    }

    return newVirtualKey;
}

QString sysTools::getpluginChildName(quint16 number)
{
    QString name;
    switch( number )
    {
        case kMkdir : name = QString("make dir");break;
        case kTimer : name = QString("kTimer");break;
        case kTick : name = QString("kTick");break;
        default:break;
    }
    return name;
}
