#include "keydefine.h"
#include "ui_keydefine.h"

keyDefine::keyDefine(QWidget *parent) :
    ui(new Ui::keyDefine)
{
    Q_UNUSED(parent);
    ui->setupUi(this);
    setWidget = this;
    type = kTypeEndpoint;
}

keyDefine::~keyDefine()
{
    delete ui;
}

void keyDefine::keypressed(bool)
{

}
void keyDefine::upDatePic(QPixmap)
{

}
void keyDefine::keypressedGUI()
{

}
void keyDefine::keyDoubleClickGUI()
{

}
void keyDefine::revertSystemInfo(QVariant,QVariant)
{

}
void keyDefine::createdVirtual()
{
    imageID = _imageList[0].imageID;
}

QVariant keyDefine::getConfig()
{
    return 0;
}
void keyDefine::SetConfig(QVariant)
{

}
