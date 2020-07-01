#include "imagemap.h"

imageMap::imageMap(QObject *parent) : QObject(parent)
{

}

int imageMap::findEmptyId()
{
    for ( int i = 0; i < INT_MAX; i++) {
        if( !sysImageList.contains(i)) return i;
    }
    return -1;
}
int imageMap::RegisterImapge(QPixmap image)
{
    int id = findEmptyId();
    if( id != -1 )
    {
        sysImageList.insert(id,image);
    }
    return id;
}
QPixmap imageMap::findImage(int id)
{
    if( sysImageList.contains(id))
    {
        return sysImageList[id];
    }
    return QPixmap();
}

imageMap uImageMap;
