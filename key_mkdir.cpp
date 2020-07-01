#include "key_mkdir.h"

key_mkdir::key_mkdir()
{
    type = kTypeDIR;
}

void key_mkdir::keypressedGUI()
{

}
void key_mkdir::keyDoubleClickGUI()
{
    emit sendSystemInfo( kMsgsetPage,_pageIndex);
}

void key_mkdir::revertSystemInfo(QVariant pid,QVariant pdata)
{
    Q_UNUSED(pid)
    if( pid.toInt() == kMsgsetPageIndex )
    {
        _pageIndex = pdata.toInt();
    }
    else if( pid.toInt() == kMsgRemovePage )
    {
        emit sendSystemInfo(kMsgRemovePage,_pageIndex);
    }
}

void key_mkdir::createdVirtual()
{
    if( type == kTypeDIR )
    {
        emit sendSystemInfo(kMsgMkdir,0);
        imageID = _imageList[0].imageID;
        //picdef->pic = _imageList[0].childPixmap;
        //picdef->pic.load(":/icons/icon/dir.png");
    }
    else if( type == kTypeBack )
    {
        imageID = _imageList[1].imageID;
        //picdef->pic = _imageList[1].childPixmap;
        //picdef->pic.load(":/icons/icon/buckdir.png");
    }
}

QVariant key_mkdir::getConfig()
{
    QJsonObject jsonObject;
    jsonObject.insert("pageIndex",_pageIndex);
    return jsonObject;
}
void key_mkdir::SetConfig(QVariant data)
{
    QJsonObject jsonObject = data.toJsonObject();
    if( jsonObject.contains("pageIndex"))
    {
        _pageIndex = jsonObject["pageIndex"].toInt();
    }
}


