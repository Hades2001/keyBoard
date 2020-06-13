#ifndef FUNTIONTREE_H
#define FUNTIONTREE_H

#include <QObject>
#include <QWidget>
#include <QTreeWidget>
#include <QMimeData>
#include <QDrag>
#include <QDragEnterEvent>
#include <QDebug>

class FuntionTree : public QTreeWidget
{

public:
    explicit FuntionTree(QWidget *parent);
protected:
    QMimeData *	mimeData(const QList<QTreeWidgetItem *> items) const;
};

#endif // FUNTIONTREE_H
