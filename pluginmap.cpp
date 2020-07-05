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

    QJsonObject configJsonOBj = sysconfig->getConfigJsonOBJ();
    QList<QString> keys = ptr->childImageMap.keys();

    if( configJsonOBj.contains("plugin"))
    {
        QJsonObject PluginJsonOBJ_n = configJsonOBj["plugin"].toObject();
        if( PluginJsonOBJ_n.contains(name))
        {
            QJsonObject PluginChildJsonOBJ = PluginJsonOBJ_n[name].toObject();
            foreach( QString childname, keys )
            {
                int size = ptr->childImageMap[childname].imageList.size();
                if( PluginChildJsonOBJ.contains(childname))
                {
                    QJsonArray imageJsonArray = PluginChildJsonOBJ[childname].toArray();
                    qDebug()<<childname;
                    for ( int i = 0; i < size; i++ ) {
                        QPixmap image = ptr->childImageMap[childname].imageList[i].childPixmap;
                        int imageID = imageJsonArray.at(i).toInt();
                        qDebug()<<"Set Plugin"<<name<<":"<<childname<<" Image "<<QString::number(i)<<" ID "<<imageJsonArray.at(i).toInt();
                        uImageMap.SetImageToID(imageID,image,imageMap::kASysImage);
                        ptr->childImageMap[childname].imageList[i].imageID = imageID;
                    }
                }
                else
                {
                    for ( int i = 0; i < size; i++ ) {
                        QPixmap image = ptr->childImageMap[childname].imageList[i].childPixmap;
                        int imageID = uImageMap.RegisterImapge(image,imageMap::kASysImage);
                        ptr->childImageMap[childname].imageList[i].imageID = imageID;
                    }
                }
            }
            return;
        }
    }

    foreach( QString childname, keys )
    {
        int size = ptr->childImageMap[childname].imageList.size();

        qDebug()<<"Register:"<<name<<":"<<childname<<"Image List size:"<<QString::number(size);
        for ( int i = 0; i < size; i++ ) {
            QPixmap image = ptr->childImageMap[childname].imageList[i].childPixmap;
            int imageID = uImageMap.RegisterImapge(image,imageMap::kASysImage);
            ptr->childImageMap[childname].imageList[i].imageID = imageID;
        }
    }
}

pluginMap uPluginMap;


