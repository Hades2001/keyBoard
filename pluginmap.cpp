#include "pluginmap.h"

pluginMap::pluginMap()
{
    Map.clear();
}

pluginMap::~pluginMap()
{

}

void pluginMap::Register(QString name,PluginInterface *ptr)
{
    Map.insert(name,ptr);

    QList<QString> keys = ptr->childImageMap.keys();

    foreach( QString childname, keys )
    {
        int size = ptr->childImageMap[childname].imageList.size();

        qDebug()<<"Register:"<<name<<":"<<childname<<"Image List size:"<<QString::number(size);
        for ( int i = 0; i < size; i++ ) {
            QPixmap image = ptr->childImageMap[childname].imageList[i].childPixmap;
            int imageID = uImageMap.RegisterImapge(image);
            ptr->childImageMap[childname].imageList[i].imageID = imageID;
        }
    }
}

pluginMap uPluginMap;


