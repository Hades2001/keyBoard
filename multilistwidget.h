#ifndef MULTILISTWIDGET_H
#define MULTILISTWIDGET_H

#include <QObject>
#include <QListWidget>
#include <QMimeData>

#include <QEvent>
#include <QDragEnterEvent>
#include <QDragLeaveEvent>
#include <QMimeData>
#include <QDebug>

#include <QMenu>
#include <QAction>

#include <virtualkey.h>
#include "pluginmap.h"

class MultiListWidget : public QListWidget
{
    Q_OBJECT
public:
    explicit MultiListWidget(QWidget *parent = nullptr);

signals:

public slots:

protected:
    void dragEnterEvent(QDragEnterEvent *event);
    void dragLeaveEvent(QDragLeaveEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
    void dropEvent(QDropEvent *event);
    void contextMenuEvent( QContextMenuEvent * event );

private:
    QString QMenuStyleSheet="QMenu{background-color: rgb(30, 30, 30);color: rgb(255, 255, 255); width: 120px;}\
                             QMenu::item {height:30px; width:120px; padding-left:5px; background-color: rgb(30, 30, 30); color: rgb(255, 255, 255);}\
                             QMenu::item:selected{background-color: rgb(255, 200, 0);color: rgb(30, 30, 30)}";

    QMenu*      popMenu;
    QAction*    Menudelete;


};

#endif // MULTILISTWIDGET_H
