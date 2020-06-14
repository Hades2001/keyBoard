#include "virtualpage.h"
#include "ui_virtualpage.h"

virtualPage::virtualPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::virtualPage)
{
    ui->setupUi(this);
    creatPage();
}

virtualPage::virtualPage(QWidget *parent,quint16 column, quint16 row) :
    QWidget(parent),
    ui(new Ui::virtualPage)
{
    ui->setupUi(this);
    _column = column;
    _row = row;
    creatPage();
}
virtualPage::~virtualPage()
{
    delete ui;
}

void virtualPage::creatPage()
{
    _btnGroup = new QButtonGroup();
    this->resize(_column*110 - 10,_row*110 - 10);

    for( int x = 0; x < _column; x++ )
    {
        for( int y = 0; y < _row; y++ )
        {
            ToolsButton *btn0 = new ToolsButton(this);
            _btnGroup->addButton(btn0,x * _row + y);
            btn0->setGeometry(x * 110 ,y * 110,100,100);
            btn0->show();

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

            connect(btn0,&ToolsButton::sendSystemInfo,this,[=](int, QVariant,QVariant){

            });
        }
    }
    /*
    ToolsButton *btn0ptr = static_cast<ToolsButton*>(_btnGroup->button(0));
    KeyTimer *timer = new KeyTimer();
    btn0ptr->setVirtualKeyPtr(timer);
    */
}

void virtualPage::setBtnClassPtr(int number,VirtualKey *ptr)
{
    ToolsButton *btn0ptr = static_cast<ToolsButton*>(_btnGroup->button(number));
    btn0ptr->setVirtualKeyPtr(ptr);
}
