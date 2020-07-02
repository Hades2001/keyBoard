#include "keyexec.h"

keyExec::keyExec()
{
    type = kTypeEndpoint;
    setWidget = new QWidget();

}

keyExec::~keyExec()
{

}

void keyExec::keypressed(bool)
{

}

void keyExec::upDatePic(QPixmap)
{

}
void keyExec::keypressedGUI()
{

}
void keyExec::keyDoubleClickGUI()
{

}
void keyExec::revertSystemInfo(QVariant,QVariant)
{

}
void keyExec::createdVirtual()
{
    imageID = _imageList[0].imageID;
    QLineEdit *lineedit = new QLineEdit("",setWidget);
    lineedit->setGeometry(0,0,100,30);
}

QVariant keyExec::getConfig()
{
    return QVariant("");
}

void keyExec::SetConfig(QVariant)
{

}

