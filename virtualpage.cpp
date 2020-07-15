#include "virtualpage.h"
#include "ui_virtualpage.h"

virtualPage::virtualPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::virtualPage)
{
    ui->setupUi(this);
    creatPage();    
}

virtualPage::virtualPage(QWidget *parent, int column, int row) :
    QWidget(parent),
    ui(new Ui::virtualPage)
{
    ui->setupUi(this);
    _column = column;
    _row = row;
    creatPage();
}

virtualPage::virtualPage(QWidget *parent, int column, int row, QJsonArray json):
    QWidget(parent),
    ui(new Ui::virtualPage)
{
    ui->setupUi(this);
    _column = column;
    _row = row;
    creatPageFromConfigFile(json);
}
virtualPage::~virtualPage()
{
    delete ui;
}

void virtualPage::creatPage()
{
    _btnGroup = new QButtonGroup();
    this->resize(_column*110 - 10,_row*110 - 10);
    this->setMinimumSize(_column*110 - 10,_row*110 - 10);

    for( int x = 0; x < _column; x++ )
    {
        for( int y = 0; y < _row; y++ )
        {
            ToolsButton *btn0 = new ToolsButton(this);
            _btnGroup->addButton(btn0,y*_column + x);
            btn0->setGeometry(x * 110 ,y * 110,100,100);
            btn0->show();

            btn0->setbtnNumber(y*_column + x);

            connect(btn0,&ToolsButton::dragEnter,this,[=](){
                _btnGroup->setExclusive(false);
                if( _btnGroup->checkedId() < 0 )
                {
                    _btnGroup->setExclusive(true);
                    return;
                }
                _btnGroup->button(_btnGroup->checkedId())->setChecked(false);
            });

            connect(btn0,&ToolsButton::sendData,this,[=](int, QByteArray){

            });

            connect(btn0,&ToolsButton::pressed,this,[=](int number){
                _btnGroup->setExclusive(true);
                emit sendSystemInfo(number,
                                    VirtualKey::kMsgShowKeyPtr,
                                    QVariant::fromValue(getBtnClassPtr(number)));

                //emit btnpressed(number,getBtnClassPtr(number));
            });


            connect(btn0,&ToolsButton::sendSystemInfo,this,&virtualPage::sendInfo);
        }
    }
    /*
    ToolsButton *btn0ptr = static_cast<ToolsButton*>(_btnGroup->button(0));
    KeyTimer *timer = new KeyTimer();
    btn0ptr->setVirtualKeyPtr(timer);
    */
}

int virtualPage::creatPageFromConfigFile(QJsonArray jsonConfig)
{
    _btnGroup = new QButtonGroup();
    this->resize(_column*110 - 10,_row*110 - 10);

    QJsonObject jsonBtnOBJ;
    for( int x = 0; x < _column; x++ )
    {
        for( int y = 0; y < _row; y++ )
        {
            int BtnID = y*_column + x;

            if( !jsonConfig.contains(BtnID))
            {
                return -1;
            }
            jsonBtnOBJ = jsonConfig[BtnID].toObject();

            if( jsonBtnOBJ["btnID"].toInt() != BtnID )
            {
                qWarning("btn ID Error");
                return -1;
            }

            if( !jsonBtnOBJ.contains("itemName"))
            {
                return -1;
            }
            QString itemName = jsonBtnOBJ["itemName"].toString();
            QString childName = jsonBtnOBJ["childName"].toString();

            //qDebug()<<QString::number(BtnID)<<itemName<<QString::number(ChildID);

            ToolsButton *btn0 = new ToolsButton(this);
            _btnGroup->addButton(btn0,BtnID);
            btn0->setGeometry(x * 110 ,y * 110,100,100);
            btn0->show();

            btn0->setbtnNumber(BtnID);

            connect(btn0,&ToolsButton::dragEnter,this,[=](){
                _btnGroup->setExclusive(false);
                if( _btnGroup->checkedId() < 0 )
                {
                    _btnGroup->setExclusive(true);
                    return;
                }
                _btnGroup->button(_btnGroup->checkedId())->setChecked(false);
            });

            connect(btn0,&ToolsButton::sendData,this,[=](int, QByteArray){

            });

            connect(btn0,&ToolsButton::pressed,this,[=](int number){
                _btnGroup->setExclusive(true);
                emit sendSystemInfo(number,
                                    VirtualKey::kMsgShowKeyPtr,
                                    QVariant::fromValue(getBtnClassPtr(number)));

                //emit btnpressed(number,getBtnClassPtr(number));
            });

            connect(btn0,&ToolsButton::sendSystemInfo,this,&virtualPage::sendInfo);

            PluginInterface *plugin = uPluginMap.Map[QString(itemName)];

            VirtualKey *VirtualKeyptr = plugin->creatChildPtr(childName);
            VirtualKeyptr->imageID = jsonBtnOBJ["imageID"].toInt();
            btn0->setVirtualKeyPtr(VirtualKeyptr);
        }
    }
    return 0;
}

int virtualPage::setBtnFromConfigFile(QJsonArray jsonConfig)
{
    QJsonObject jsonBtnOBJ;

    for( int x = 0; x < _column; x++ )
    {
        for( int y = 0; y < _row; y++ )
        {
            int BtnID = y*_column + x;
            /*
            if( !jsonConfig.contains(BtnID))
            {
                qWarning("Fine btn ID Error");
                return -1;
            }
            */
            jsonBtnOBJ = jsonConfig[BtnID].toObject();

            if( jsonBtnOBJ["btnID"].toInt() != BtnID )
            {
                qWarning("btn ID Error");
                return -1;
            }

            if( !jsonBtnOBJ.contains("itemName"))
            {
                return -1;
            }
            QString itemName = jsonBtnOBJ["itemName"].toString();
            QString childName = jsonBtnOBJ["childName"].toString();
            int type = jsonBtnOBJ["type"].toInt();

            if( type != 0 )
            {
                PluginInterface *plugin = uPluginMap.Map[QString(itemName)];

                VirtualKey *VirtualKeyptr = plugin->creatChildPtr(childName);
                VirtualKeyptr->type = type;
                setBtnClassPtr(BtnID,VirtualKeyptr);

                QJsonObject jsonkeyconfigOBJ = jsonBtnOBJ["config"].toObject();

                //qDebug()<<"BTN:"<<QString::number(BtnID)<<" "<<jsonkeyconfigOBJ;

                VirtualKeyptr->SetConfig(jsonkeyconfigOBJ);
                VirtualKeyptr->imageID = jsonBtnOBJ["imageID"].toInt();
            }
        }
    }
    return 0;
}

void virtualPage::sendInfo(int id, QVariant pid,QVariant pdata)
{
    emit sendSystemInfo(id,pid,pdata);
}

QJsonObject virtualPage::generateConfig()
{
    int btnNumber = _column * _row;

    QJsonObject pageJsonOBJ;
    QJsonArray keyJsonArray;

    pageJsonOBJ.insert("pageIndex",pageIndex);

    for (int i = 0; i < btnNumber; i++ ) {
        ToolsButton *btn =  static_cast<ToolsButton*>(_btnGroup->button(i));
        VirtualKey *ptr = btn->getVirtualKeyPtr();

        QJsonObject keyjsonObj;
        keyjsonObj.insert("type",ptr->type);
        keyjsonObj.insert("btnID",i);
        keyjsonObj.insert("itemName",ptr->parentsName);
        keyjsonObj.insert("childName",ptr->childName);
        keyjsonObj.insert("config",ptr->getConfig().toJsonObject());
        keyjsonObj.insert("imageID",ptr->imageID);
        keyJsonArray.insert(i,keyjsonObj);
        }

    pageJsonOBJ.insert("keyArray",keyJsonArray);
    return pageJsonOBJ;
}

void virtualPage::setBtnClassPtr(int number,VirtualKey *ptr)
{
    ToolsButton *btn0ptr = static_cast<ToolsButton*>(_btnGroup->button(number));
    btn0ptr->setVirtualKeyPtr(ptr);
}

void virtualPage::removeBtnClassPtr(int index)
{
    ToolsButton *btn0ptr = static_cast<ToolsButton*>(_btnGroup->button(index));
    btn0ptr->removeVirtualKeyPtr();
}

VirtualKey* virtualPage::getBtnClassPtr(int index)
{
    ToolsButton *btn0ptr = static_cast<ToolsButton*>(_btnGroup->button(index));
    return  btn0ptr->getVirtualKeyPtr();
}

void virtualPage::revertSystemInfo(int number, QVariant pid ,QVariant pdata)
{
    if( number < 0 )
    {
        return;
    }
    else
    {
        ToolsButton *btn =  static_cast<ToolsButton*>(_btnGroup->button(number));
        btn->revertSystemInfo(pid,pdata);
    }
}

void virtualPage::sendSystemInfoToAll(QVariant pid,QVariant pdata)
{
    int btnNumber = _column * _row;
    for (int i = 0; i < btnNumber; i++ ) {
        ToolsButton *btn =  static_cast<ToolsButton*>(_btnGroup->button(i));
        btn->sendSystemInfo(i,pid,pdata);
    }
}
