#include "funtiontree.h"

FuntionTree::FuntionTree(QWidget *parent):QTreeWidget(parent)
{
    setDefaultDropAction(Qt::MoveAction);
    setDragDropMode(QAbstractItemView::DragOnly);
}

QMimeData *FuntionTree::mimeData(const QList<QTreeWidgetItem *> items) const
{
    Q_UNUSED(items);
    qDebug() <<"[-----]"<< this->currentItem()->text(0)<<this->currentItem()->data(0,1);
    QByteArray itemData;
    itemData.resize(2);
    itemData[0] = char(this->currentItem()->data(0,1).toInt());

    QMimeData *mimeData = new QMimeData;
    mimeData->setData("application/x-qabstractitemmodeldatalist", itemData);
    mimeData->setData("application/PluginName", QString("Name is this").toLatin1());
    return mimeData;
}


