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
        case 0 : newVirtualKey = new KeyTimer;break;
        case 1 : newVirtualKey = new KeyTimer;break;
        case 2 : newVirtualKey = new KeyTimer;break;
        case 3 : newVirtualKey = new KeyTimer;break;
        default: newVirtualKey = nullptr; break;
    }

    return newVirtualKey;
}
