#ifndef TOOLSBUTTON_H
#define TOOLSBUTTON_H

#include <QWidget>
#include <QPushButton>
#include <QEvent>
#include <QDragEnterEvent>
#include <QDragLeaveEvent>
#include <QMimeData>
#include <QDebug>
#include <QPainter>
#include <QTimer>
#include <virtualkey.h>

#include <QListWidget>
#include <QMenu>
#include <QAction>
#include <QContextMenuEvent>
#include <QMouseEvent>


#include "pulginmap.h"


class ToolsButton : public QPushButton
{
    Q_OBJECT
public:
    explicit ToolsButton(QWidget *parent);

public:
    enum BtnState{
        k_Btn_IDLE = 0,
        k_Btn_Enter,
        k_Btn_Checked,
        k_Btn_DragEnter,
        k_Btn_Max,
    };
public:
    void setVirtualKeyPtr(VirtualKey *VirtualKeyptr);
    VirtualKey* getVirtualKeyPtr(){return _VirtualKeyptr;}
    void setbtnNumber(int num ){ _btnnumber = num; }
    void revertSystemInfo(QVariant pid ,QVariant pdata) { _VirtualKeyptr->revertSystemInfo(pid,pdata);}
protected:
    void dragEnterEvent(QDragEnterEvent *event);
    void dragLeaveEvent(QDragLeaveEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
    void dropEvent(QDropEvent *event);
    void enterEvent(QEvent *e);
    void leaveEvent(QEvent *e);
    void paintEvent(QPaintEvent *e);

    void contextMenuEvent( QContextMenuEvent * event );

private:
    QTimer     *_doubleClickTimer;
    bool        _doubleClickFlag = false;
    VirtualKey *_VirtualKeyptr;
    BtnState    _state = k_Btn_IDLE;
    int         _btnnumber;

    QMenu *_contextMenu;
    QAction *_addAction;
    QAction *_delAction;

    QString QMenuStyleSheet="QMenu{background-color: rgb(30, 30, 30);color: rgb(255, 255, 255);}\
                             QMenu::item {height:30px; width:70px; padding-left:5px; background-color: rgb(30, 30, 30); color: rgb(255, 255, 255);}\
                             QMenu::item:selected{background-color: rgb(255, 200, 0);color: rgb(30, 30, 30)}";

signals:
    void dragEnter();
    void doubleClick(int);
    void pressed(int);
    void sendData(int, QByteArray);
    void sendSystemInfo(int, QVariant,QVariant);
};

#endif // TOOLSBUTTON_H
