#include "treeitemdelegate.h"

TreeItemDelegate::TreeItemDelegate(QObject *parent)
{
    Q_UNUSED(parent)
}

void TreeItemDelegate::paint(QPainter *painter,const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    //painter->save();
    QRect rect = option.rect;
    // |-------------------------------------------|
    // |      |        |                           |
    // |   >  |  ICON  |   NAME                    |
    // |      |        |                           |
    // |-------------------------------------------|
    // 0  5  30       70   80
    QColor bkcolor,textColor;
    if( option.state & QStyle::State_MouseOver)
    {
        bkcolor = QColor(255,200,0);
        textColor = QColor(0x21,0x21,0x21);
    }
    else
    {
        bkcolor = QColor(0x21,0x21,0x21);
        textColor = QColor(255,255,255);
    }

    QBrush brush(bkcolor);
    QPen   pen(brush,0,Qt::NoPen);

    painter->setBrush(brush);
    painter->setPen(pen);
    painter->drawRect(rect);

    QRect textRect (rect.x() + 80,rect.y(),rect.width() - 90,rect.height());
    QRect FlagRect (rect.x() + 5,rect.y() + 10,30,30);
    QRect ImageRect(rect.x() + 55 - (( rect.height() - 20 ) / 2 ),rect.y() + 10,rect.height() - 20,rect.height() - 20);

    pen.setColor(textColor);
    pen.setStyle(Qt::SolidLine);

    painter->font();
    QFont font = painter->font();
    //QFont font("Bahnschrift Light");

    if( index.data(Qt::UserRole + 1).toInt() == 0 )
    {
        if( option.state & QStyle::State_Open)
        {
            painter->drawPixmap(FlagRect,QPixmap(":/icons/icon/branch_open.png"));
        }
        else
        {
            painter->drawPixmap(FlagRect,QPixmap(":/icons/icon/branch_close.png"));
        }
        pen.setWidth(5);
        font.setPixelSize(16);
        font.setBold(true);
    }
    else
    {
        pen.setWidth(3);
        font.setPixelSize(15);
        font.setBold(false);
    }

    QPixmap iconImage = index.data(Qt::UserRole + 4).value<QPixmap>();

    painter->drawPixmap(ImageRect,iconImage);
    painter->setPen(pen);
    painter->setFont(font);
    painter->drawText(textRect,Qt::AlignVCenter | Qt::AlignLeft,index.data().toString());



    //qInfo("state %08X",option.state);//State_MouseOver

    /*
    QVariant imageData = index.data(Qt::UserRole + 1);
    QPixmap image = imageData.value<QPixmap>();

    painter->drawPixmap(rect,image);
    */

    //QStyledItemDelegate::paint(painter,option,index);
}

QSize TreeItemDelegate::sizeHint(const QStyleOptionViewItem &option,const QModelIndex &index) const
{
    QSize s = QStyledItemDelegate::sizeHint(option,index);
    if( index.data(Qt::UserRole + 1).toInt() == 0 )
    {
        s.setHeight(50);
    }
    else
    {
        s.setHeight(40);
    }
    return s;
}
