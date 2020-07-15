#include "keymultiopera.h"
#include "ui_keymultiopera.h"

keyMultiOpera::keyMultiOpera(QWidget *parent) :
    ui(new Ui::keyMultiOpera)
{
    Q_UNUSED(parent)
    ui->setupUi(this);
    setWidget = this;
    type = kTypeMultiOperation;

    QListWidget* m_ListSerial = new QListWidget(this);
    m_ListSerial->setItemDelegate(new NoFocusFrameDelegate(this));
    ui->cb_operation->setModel(m_ListSerial->model());
    ui->cb_operation->setView(m_ListSerial);

    ui->cb_operation->addItem(tr("顺序操作"),0);
    ui->cb_operation->addItem(tr("随机操作"),1);
    ui->cb_operation->addItem(tr("倒序操作"),2);
}

keyMultiOpera::~keyMultiOpera()
{
    delete ui;
}

void keyMultiOpera::keypressed(bool){}
void keyMultiOpera::upDatePic(QPixmap){}
void keyMultiOpera::keypressedGUI(){}
void keyMultiOpera::keyDoubleClickGUI()
{
    emit sendSystemInfo(kMsgSetMultiPage,QVariant::fromValue(_MultiOperationPagePtr));
}
void keyMultiOpera::revertSystemInfo(QVariant msg,QVariant data)
{
    int msgType = msg.toInt();
    switch (msgType) {
        case kMsgsetPageIndex:
            _parentIndex = data.toInt();
            qInfo("parent page Index %d",_parentIndex);
        break;
    }
}
void keyMultiOpera::createdVirtual()
{
    imageID = _imageList[0].imageID;

    _MultiOperationPagePtr = new MultiOperation();
    connect(_MultiOperationPagePtr,&MultiOperation::backToParent,this,[=](){
        emit sendSystemInfo(kMsgsetPage,_parentIndex);
    });

    emit sendSystemInfo(kMsgAddMultiPage,QVariant::fromValue(_MultiOperationPagePtr));
}

QVariant keyMultiOpera::getConfig(){ return 0;}
void keyMultiOpera::SetConfig(QVariant){}
void keyMultiOpera::setEnabledfromFlag(){}
