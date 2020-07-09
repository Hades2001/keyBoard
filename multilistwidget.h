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

#include <virtualkey.h>

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

};

#endif // MULTILISTWIDGET_H
