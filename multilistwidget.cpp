#include "multilistwidget.h"

MultiListWidget::MultiListWidget(QWidget *parent) : QListWidget(parent)
{

}

void MultiListWidget::dragEnterEvent(QDragEnterEvent *event)
{
    QByteArray itemType = event->mimeData()->data("application/type");
    if( itemType.at(0) == VirtualKey::kTypeDIR )
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
    if( itemType.at(0) == VirtualKey::kTypeDIR )
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

    QByteArray itemType = event->mimeData()->data("application/type");
    if( itemType.at(0) == VirtualKey::kTypeDIR )
    {
        event->ignore();
    }
    else if (event->source() == this) {
        event->setDropAction(Qt::MoveAction);
        event->accept();
    } else {
        event->acceptProposedAction();
    }
}
