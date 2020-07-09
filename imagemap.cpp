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
int imageMap::RegisterImapge(QPixmap image,int Attributes )
{
    int id = findEmptyId();

    if( id != -1 )
    {
        imageBox_t box;
        box.image = image;
        box.Attributes = Attributes;
        box.usedNumber = 0;
        box.id = id;
        sysImageList.insert(id,box);
        sysImageList.begin();
        //qInfo("image map size : %d",sysImageList.size());
        _operatedFlag = true;
    }

    return id;
}
QPixmap imageMap::findImage(int id)
{
    if( sysImageList.contains(id))
    {
        return sysImageList[id].image;
    }
    return QPixmap(":/icons/icon/NoImage.png");
}

int imageMap::removePic(int id )
{
    if( sysImageList.contains(id))
    {
        QString imagePath = sysconfig->getImagePath();
        QString imageName = "image" + QString::number(id) + ".png";
        imagePath = imagePath + '/' + imageName;

        if( QFile::exists(imagePath))
        {
            QFile::remove(imagePath);
        }
        sysImageList.remove(id);
    }
    else
    {
        return -1;
    }
    return 0;
}

int imageMap::SetImageToID(int id ,QPixmap image, int Attributes )
{
    imageBox_t box;
    box.image = image;
    box.Attributes = Attributes;
    box.usedNumber = 0;
    box.id = id;


    sysImageList.insert(id,box);

    _operatedFlag = true;
    return 0;
}

int imageMap::replaceImage(int id ,QPixmap image, int Attributes )
{
    if( !sysImageList.contains(id))
    {
        _operatedFlag = true;
        return RegisterImapge(image,Attributes);
    }
    else
    {
        _operatedFlag = true;
        imageBox_t box = sysImageList[id];
        if(box.Attributes != kANormal)
        {
            return RegisterImapge(image,Attributes);
        }
        else
        {
            box.image = image;
            return id;
        }
    }
}

QJsonObject imageMap::saveImage()
{
    QJsonObject imageJsonOBj;
    QJsonArray  imageJsonArray;

    foreach(imageBox_t box, sysImageList)
    {
        QJsonObject imageConfigJsonOBJ;
        imageConfigJsonOBJ.insert("id",box.id);
        imageConfigJsonOBJ.insert("Attributes",box.Attributes);

        if(box.Attributes != kASysImage )
        {
            QString imagePath = sysconfig->getImagePath();
            QString imageName = "image" + QString::number(box.id) + ".png";
            imagePath = imagePath + '/' + imageName;

            if( _operatedFlag )
            {
                box.image.save(imagePath);
            }
            imageConfigJsonOBJ.insert("filePath",imageName);
        }
        imageJsonArray.append(imageConfigJsonOBJ);
    }
    imageJsonOBj.insert("imageArray",imageJsonArray);

    return imageJsonOBj;
}

int imageMap::readFromJsonConfig(QJsonObject jsonOBJ)
{
    if( !jsonOBJ.contains("imageArray")) return -1;
    QJsonArray imageArray = jsonOBJ["imageArray"].toArray();
    for(int i = 0; i < imageArray.size(); i++ )
    {
        QJsonObject imageOBJ =  imageArray.at(i).toObject();
        imageBox_t box;
        box.Attributes = imageOBJ["Attributes"].toInt();
        box.id = imageOBJ["id"].toInt();
        if(box.Attributes == kANormal )
        {
            QString imageName = imageOBJ["filePath"].toString();
            QString imagePath = sysconfig->getImagePath();
            imagePath = imagePath + '/' + imageName;
            if( QFile::exists(imagePath))
            {
                box.image.load(imagePath);
                sysImageList.insert(box.id,box);
            }
            else
            {
                qDebug()<<imageName<<"find error";
            }
        }
    }
    return 0;
}

int imageMap::readPluginImageFromJson(QJsonObject jsonOBJ)
{
    QList<PluginInterface::childImage_t*> NewimagePtrList;
    QList<QString> pluginNameList = uPluginMap.Map.keys();

    qDebug()<<"readPluginImageFromJson";

    foreach( QString pluginName, pluginNameList)
    {
        bool hasPluginInConfig = false;
        bool hasChildInConfig = false;
        QJsonObject PluginJson;
        if( jsonOBJ.contains(pluginName))
        {
            qDebug()<<"find plugin"<<pluginName;
            hasPluginInConfig = true;
            PluginJson = jsonOBJ[pluginName].toObject();
        }

        PluginInterface * ptr = uPluginMap.Map[pluginName];
        QList<QString> childNameList = ptr->metaMap.keys();
        foreach( QString childName, childNameList)
        {
            QJsonArray childArray;
            if( hasPluginInConfig )
            {
                if( !PluginJson.contains(childName))
                {
                    hasChildInConfig = false;
                }
                else
                {
                    qDebug()<<"find child "<<childName;
                    hasChildInConfig = true;
                    childArray = PluginJson[childName].toArray();
                }
            }
            PluginInterface::childImage_t* childImagePtr = &ptr->childImageMap[childName];
            int imageListSize = childImagePtr->imageList.size();
            for( int i = 0; i < imageListSize; i++ )
            {
                if(( hasPluginInConfig )&&( hasChildInConfig )&&( childArray.size() > i ))
                {
                    int id = childArray[i].toInt();
                    qDebug()<<"set"<<pluginName + '.' + childName<<" id = "<<QString::number(id);
                    uImageMap.SetImageToID(id,childImagePtr->imageList[i].childPixmap,imageMap::kASysImage);
                    childImagePtr->imageList[i].imageID = id;
                    continue;
                }
                qDebug()<<"New"<<pluginName + '.' + childName;
                NewimagePtrList.append(childImagePtr);
            }
        }
    }
    if( !NewimagePtrList.empty())
    {
        int NewSize = NewimagePtrList.size();
        for( int i = 0; i < NewSize; i++ )
        {
            int imageListSize = NewimagePtrList.at(i)->imageList.size();
            for( int count = 0; count < imageListSize; count++ )
            {

                QPixmap image = NewimagePtrList.at(i)->imageList.at(count).childPixmap;
                int NewimageID = uImageMap.RegisterImapge(image,imageMap::kASysImage);
                NewimagePtrList[i]->imageList[count].imageID = NewimageID;
                qDebug()<<"New Image id = "<<QString::number(NewimageID);
            }
        }
    }
    return 0;
}



imageMap uImageMap;
