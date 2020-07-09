#include "funtiontree.h"

FuntionTree::FuntionTree(QWidget *parent):QTreeWidget(parent)
{
    setDefaultDropAction(Qt::MoveAction);
    setDragDropMode(QAbstractItemView::DragOnly);
}

QMimeData *FuntionTree::mimeData(const QList<QTreeWidgetItem *> items) const
{
    Q_UNUSED(items);
    QByteArray itemData;
    itemData.resize(1);

    QString pluginname = this->currentItem()->data(0,Qt::UserRole+2).toString();
    QString childname = this->currentItem()->data(0,Qt::UserRole+3).toString();
    itemData[0] = char(this->currentItem()->data(0,Qt::UserRole+5).toInt());

    //qDebug() <<"[-----]"<< this->currentItem()->text(0)<<pluginname<<this->currentItem()->data(0,1);

    QMimeData *mimeData = new QMimeData;
    mimeData->setData("application/x-qabstractitemmodeldatalist", childname.toLatin1());
    mimeData->setData("application/PluginName", pluginname.toLatin1());
    mimeData->setData("application/type",itemData);
    return mimeData;
}


