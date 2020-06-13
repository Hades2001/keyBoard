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
#include <virtualkey.h>


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
protected:
    void dragEnterEvent(QDragEnterEvent *event);
    void dragLeaveEvent(QDragLeaveEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
    void dropEvent(QDropEvent *event);
    void enterEvent(QEvent *e);
    void leaveEvent(QEvent *e);
    void paintEvent(QPaintEvent *e);

private:
    VirtualKey *_VirtualKeyptr;
    BtnState    _state = k_Btn_IDLE;

signals:
    void dragEnter();
};

#endif // TOOLSBUTTON_H