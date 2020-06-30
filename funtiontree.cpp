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
    itemData.resize(2);
    itemData[0] = char(this->currentItem()->data(0,1).toInt());
    QString pluginname = this->currentItem()->data(1,1).toString();

    qDebug() <<"[-----]"<< this->currentItem()->text(0)<<pluginname<<this->currentItem()->data(0,1);

    QMimeData *mimeData = new QMimeData;
    mimeData->setData("application/x-qabstractitemmodeldatalist", itemData);
    mimeData->setData("application/PluginName", pluginname.toLatin1());
    return mimeData;
}


