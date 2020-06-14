#include "toolsbutton.h"

ToolsButton::ToolsButton(QWidget *parent):QPushButton(parent)
{
    setAcceptDrops(true);
    _VirtualKeyptr = new VirtualKey;

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

    if( _VirtualKeyptr->picList.size() != 0 )
    {
        this->setIcon(QIcon(_VirtualKeyptr->picList.at(0).pic));
    }

    this->setCheckable(true);
    connect(this,&ToolsButton::clicked,this,[=](bool clicked)
    {
        Q_UNUSED(clicked);
        this->repaint();
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
                        5,
                        Qt::SolidLine,
                        Qt::RoundCap,
                        Qt::RoundJoin));

    painter.setBrush(QBrush(QColor(0x2d,0x2d,0x2d)));
    painter.drawRoundRect(QRect(5,5,this->width()-10,this->height()-10));
    if( _VirtualKeyptr->picList.size() != 0 )
    {
        painter.drawPixmap(QRect(30,30,this->width()-60,this->height()-60),_VirtualKeyptr->picList.at(0).pic);
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
    qDebug()<<"setVirtualKeyPtr";
    if( VirtualKeyptr != nullptr )
    {
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

        if( _VirtualKeyptr->picList.size() != 0 )
        {
            this->setIcon(QIcon(_VirtualKeyptr->picList.at(0).pic));
        }
    }
}

void ToolsButton::dragEnterEvent(QDragEnterEvent *event)
{
    Q_UNUSED(event);
    if (event->mimeData()->hasFormat("application/x-qabstractitemmodeldatalist")) {
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
    if (event->mimeData()->hasFormat("application/x-qabstractitemmodeldatalist")) {
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

    /*
    PluginInterface *plugin = uPulginMap.Map[QString(itemName)];
    VirtualKey *VirtualKeyptr = plugin->getpluginChildPtr(quint16(itemData.at(0)));
    this->setVirtualKeyPtr(VirtualKeyptr);
    */
    if (event->source() == this) {
        event->setDropAction(Qt::MoveAction);
        event->accept();
    } else {
        event->acceptProposedAction();
    }
}
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

