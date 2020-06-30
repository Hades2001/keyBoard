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
    qInfo("DIR Double");
    emit sendSystemInfo( kMsgsetPage,_pageIndex);
}

void key_mkdir::revertSystemInfo(QVariant pid,QVariant pdata)
{
    Q_UNUSED(pid)
    _pageIndex = pdata.toInt();
}

void key_mkdir::createdVirtual()
{
    emit sendSystemInfo(kMsgMkdir,0);
    VirtaulKeyImage_t *picdef = new VirtaulKeyImage_t;
    if( type == kTypeDIR )
    {
        picdef->pic.load(":/icons/icon/dir.png");
    }
    else if( type == kTypeBack )
    {
        picdef->pic.load(":/icons/icon/buckdir.png");
    }
    picList.append(*picdef);
}
