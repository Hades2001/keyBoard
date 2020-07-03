#include "toolsbutton.h"

ToolsButton::ToolsButton(QWidget *parent):QPushButton(parent)
{
    setAcceptDrops(true);

    _VirtualKeyptr = new VirtualKey;
    setVirtualKeyPtr(new VirtualKey);

    this->setCheckable(true);
    connect(this,&QPushButton::clicked,this,[=](bool clicked)
    {
        Q_UNUSED(clicked);
        this->repaint();
    });

    _doubleClickTimer = new QTimer;

    connect(this,&QPushButton::pressed,this,[=]()
    {
        if( _doubleClickFlag == true )
        {
            emit doubleClick(_btnnumber);
            _VirtualKeyptr->keyDoubleClickGUI();
            _doubleClickTimer->stop();
            _doubleClickFlag = false;
        }
        else
        {
            _doubleClickFlag = true;
            _doubleClickTimer->start(200);
        }
    });

    connect(_doubleClickTimer,&QTimer::timeout,this,[=]()
    {
        emit pressed(_btnnumber);
        qDebug()<<_VirtualKeyptr->DescribeName;
        _VirtualKeyptr->keypressedGUI();
        _doubleClickFlag = false;
        _doubleClickTimer->stop();

    });

    this->setContextMenuPolicy(Qt::DefaultContextMenu);

    _contextMenu = new QMenu;
    _contextMenu->setStyleSheet(QMenuStyleSheet);

    _addAction = new QAction("copy",this);
    _delAction = new QAction("delete",this);

    _contextMenu->addAction(_addAction);
    _contextMenu->addAction(_delAction);

    connect(_delAction,&QAction::triggered,this,[=](){
        removeVirtualKeyPtr();
    });


}
void ToolsButton::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);

    QColor color;
    switch (_state) {
        case k_Btn_Checked:color = QColor(0x00,0x84,0xff);break;
        case k_Btn_Enter:color = QColor(0xb6,0xb6,0xb6);break;
        case k_Btn_DragEnter:color = QColor(0xff,0xa2,0x00);break;
        case k_Btn_IDLE:color = QColor(0x7c,0x7c,0x7c);break;
        default:color = QColor(0x7c,0x7c,0x7c);break;
    }

    if( this->isChecked() == true )
    {
        color = QColor(0x00,0x84,0xff);
    }

    painter.setPen(QPen(color,
                        4,
                        Qt::SolidLine,
                        Qt::RoundCap,
                        Qt::RoundJoin));

    painter.setBrush(QBrush(QColor(0x2d,0x2d,0x2d)));
    //painter.drawRoundRect(QRect(5,5,this->width()-10,this->height()-10));
    painter.drawRoundedRect(QRect(5,5,this->width()-10,this->height()-10),20,20);

    //painter.drawRoundedRect(QRect(5,5,this->width()-10,this->height()-10));
    if( _VirtualKeyptr->imageID != -1 )
    {
        QPixmap image =  uImageMap.findImage(_VirtualKeyptr->imageID);
        painter.drawPixmap(QRect(12,12,this->width()-24,this->height()-24),image);
    }

    painter.end();

}

void ToolsButton::enterEvent(QEvent *e)
{
    Q_UNUSED(e);
    _state = k_Btn_Enter;
    this->repaint();
    this->setText("Enter");
}
void ToolsButton::leaveEvent(QEvent *e)
{
    Q_UNUSED(e);
    _state = k_Btn_IDLE;
    this->setText("Leave");
}

void ToolsButton::setVirtualKeyPtr(VirtualKey *VirtualKeyptr)
{

    if( VirtualKeyptr != nullptr )
    {
        if( _VirtualKeyptr->type == VirtualKey::kTypeDIR )
        {
            _VirtualKeyptr->revertSystemInfo(VirtualKey::kMsgRemovePage,0);
        }

        delete _VirtualKeyptr;
        _VirtualKeyptr = VirtualKeyptr;

        connect(_VirtualKeyptr,&VirtualKey::sendData,this,[=](QByteArray data)
        {
            emit sendData(_btnnumber, data);
        });


        connect(_VirtualKeyptr,&VirtualKey::sendSystemInfo,this,[=](QVariant msgID,QVariant msgdata)
        {
            emit sendSystemInfo(_btnnumber, msgID,msgdata);
        });


        connect(_VirtualKeyptr,&VirtualKey::updateGUI,this,[=](QPixmap pic)
        {
            this->setIcon(QIcon(pic));
        });
        //qDebug()<<__FILE__<<__LINE__;

        _VirtualKeyptr->createdVirtual();

        /*
        if( _VirtualKeyptr->picList.size() != 0 )
        {
            this->setIcon(QIcon(_VirtualKeyptr->picList.at(0).pic));
        }
        */
        //qDebug()<<__FILE__<<__LINE__;

    }
}
void ToolsButton::removeVirtualKeyPtr()
{
    if( _VirtualKeyptr->type == VirtualKey::kTypeDIR )
    {
        _VirtualKeyptr->revertSystemInfo(VirtualKey::kMsgRemovePage,0);
    }

    delete _VirtualKeyptr;
    _VirtualKeyptr = new VirtualKey;
    setVirtualKeyPtr(new VirtualKey);
}

void ToolsButton::dragEnterEvent(QDragEnterEvent *event)
{
    Q_UNUSED(event);
    if( _VirtualKeyptr->type == VirtualKey::kTypeBack)
    {
        event->ignore();
    }
    else if (event->mimeData()->hasFormat("application/x-qabstractitemmodeldatalist")) {
        this->setText("Enter");
        _state = k_Btn_DragEnter;
        emit dragEnter();
        if (event->source() == this) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        } else {
            event->acceptProposedAction();
        }
    } else {
        event->ignore();
    }
}

void ToolsButton::dragLeaveEvent(QDragLeaveEvent *event)
{
    Q_UNUSED(event);
    _state = k_Btn_IDLE;
    this->setText("Leave");
}

void ToolsButton::dragMoveEvent(QDragMoveEvent *event)
{
    Q_UNUSED(event);
    if( _VirtualKeyptr->type == VirtualKey::kTypeBack)
    {
        event->ignore();
    }
    else if (event->mimeData()->hasFormat("application/x-qabstractitemmodeldatalist")) {
        if (event->source() == this) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        } else {
            event->acceptProposedAction();
        }
    } else {
        event->ignore();
    }
}
void ToolsButton::dropEvent(QDropEvent *event)
{
    Q_UNUSED(event);
    QByteArray itemData = event->mimeData()->data("application/x-qabstractitemmodeldatalist");
    QByteArray itemName = event->mimeData()->data("application/PluginName");

    qDebug()<<itemData;
    qDebug()<<QString(itemName);

    PluginInterface *plugin = uPluginMap.Map[QString(itemName)];

    VirtualKey *VirtualKeyptr = plugin->creatChildPtr(QString(itemData));

    this->setVirtualKeyPtr(VirtualKeyptr);

    if (event->source() == this) {
        event->setDropAction(Qt::MoveAction);
        event->accept();
    } else {
        event->acceptProposedAction();
    }
}

void ToolsButton::contextMenuEvent( QContextMenuEvent * event )
{
    Q_UNUSED(event)
    if(( _VirtualKeyptr->type == VirtualKey::kTypeIDLE )||\
       ( _VirtualKeyptr->type == VirtualKey::kTypeBack))
    {
        return;
    }
    _contextMenu->exec(QCursor::pos());
}
/*
void ToolsButton::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::RightButton)
    {
        _contextMenu->exec(event->globalPos());
    }
    //要继续保留QListWidget原有的点击事件.
    ToolsButton::mousePressEvent(event);
}
*/
/*
void DragWidget::dropEvent(QDropEvent *event)
{
    if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
        QByteArray itemData = event->mimeData()->data("application/x-dnditemdata");
        QDataStream dataStream(&itemData, QIODevice::ReadOnly);

        QPixmap pixmap;
        QPoint offset;
        dataStream >> pixmap >> offset;

        QLabel *newIcon = new QLabel(this);
        newIcon->setPixmap(pixmap);
        newIcon->move(event->pos() - offset);
        newIcon->show();
        newIcon->setAttribute(Qt::WA_DeleteOnClose);

        if (event->source() == this) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        } else {
            event->acceptProposedAction();
        }
    } else {
        event->ignore();
    }
}
*/

