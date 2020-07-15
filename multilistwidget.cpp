#include "multilistwidget.h"

MultiListWidget::MultiListWidget(QWidget *parent) : QListWidget(parent)
{
    this->setContextMenuPolicy(Qt::CustomContextMenu);

    popMenu = new QMenu;
    popMenu->setStyleSheet(QMenuStyleSheet);
    Menudelete = new QAction(tr("删除"),this);
    popMenu->addAction(Menudelete);

    connect(Menudelete,&QAction::triggered,this,[=](){

    });

}

void MultiListWidget::dragEnterEvent(QDragEnterEvent *event)
{
    QByteArray itemType = event->mimeData()->data("application/type");
    if(( itemType.at(0) == VirtualKey::kTypeDIR )||( itemType.at(0) == VirtualKey::kTypeMultiOperation ))
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

void MultiListWidget::dragLeaveEvent(QDragLeaveEvent *event)
{
    Q_UNUSED(event);
}

void MultiListWidget::dragMoveEvent(QDragMoveEvent *event)
{
    QByteArray itemType = event->mimeData()->data("application/type");
    if(( itemType.at(0) == VirtualKey::kTypeDIR )||( itemType.at(0) == VirtualKey::kTypeMultiOperation ))
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
void MultiListWidget::dropEvent(QDropEvent *event)
{
    Q_UNUSED(event);
    QByteArray itemData = event->mimeData()->data("application/x-qabstractitemmodeldatalist");
    QByteArray itemName = event->mimeData()->data("application/PluginName");

    qDebug()<<itemData;
    qDebug()<<QString(itemName);

    PluginInterface *plugin = uPluginMap.Map[QString(itemName)];
    QPixmap icon = plugin->childImageMap[QString(itemData)].childIcon;

    QListWidgetItem* item=new QListWidgetItem(icon,QString(itemData));
    VirtualKey *VirtualKeyptr = plugin->creatChildPtr(QString(itemData));

    QVariant ptr = QVariant::fromValue(VirtualKeyptr);

    // 1 -> plugin ptr
    // 2 -> plugin Descri name
    // 3 -> plugin icon

    item->setData(Qt::UserRole + 1,ptr);
    item->setData(Qt::UserRole + 2,plugin->childImageMap[QString(itemData)].DescribeName);
    item->setData(Qt::UserRole + 3,icon);

    //VirtualKey *VirtualKeyptr1 = item->data(Qt::UserRole + 1).value<VirtualKey *>();

    this->addItem(item);

    //QByteArray itemType = event->mimeData()->data("application/type");
    //if(( itemType.at(0) == VirtualKey::kTypeDIR )||( itemType.at(0) == VirtualKey::kTypeMultiOperation ))
    //{
    //    event->ignore();
    //}


    if (event->source() == this) {
        event->setDropAction(Qt::MoveAction);
        event->accept();
    } else {
        event->acceptProposedAction();
    }
}

void MultiListWidget::contextMenuEvent( QContextMenuEvent * event )
{
    Q_UNUSED(event)
    popMenu->exec(QCursor::pos());
}
