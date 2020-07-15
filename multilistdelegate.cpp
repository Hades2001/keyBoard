#include "multilistdelegate.h"

MultiListDelegate::MultiListDelegate(QObject *parent)
{
    Q_UNUSED(parent)
}

void MultiListDelegate::paint(QPainter *painter,const QStyleOptionViewItem &option, const QModelIndex &index) const
{
     Q_UNUSED(painter)
     Q_UNUSED(option)
     Q_UNUSED(index)

    //painter->save();
    QRect rect = option.rect;
    // |--------------------------------------|
    // | |        |                           |
    // | |  ICON  |   NAME                    |
    // | |        |                           |
    // |--------------------------------------|
    // 0 5       70   80
    qInfo("state:%08X",quint32(option.state));
    QColor bkcolor,textColor;
    if( option.state & QStyle::State_Selected)
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

    QRect textRect (rect.x() + 70, rect.y(),rect.width() - 90,rect.height());
    //QRect FlagRect (rect.x() + 5,rect.y() + 10,30,30);
    QRect ImageRect(rect.x() + 16, rect.y() + 8,rect.height() - 16,rect.height() - 16);

    pen.setColor(textColor);
    pen.setStyle(Qt::SolidLine);

    painter->font();
    QFont font = painter->font();
    //QFont font("Bahnschrift Light");

    pen.setWidth(3);
    font.setPixelSize(15);
    font.setBold(false);

    // 1 -> plugin ptr
    // 2 -> plugin Descri name
    // 3 -> plugin icon


    QPixmap iconImage = index.data(Qt::UserRole + 3).value<QPixmap>();
    QString DescriName = index.data(Qt::UserRole + 2).toString();
    painter->drawPixmap(ImageRect,iconImage);
    painter->setPen(pen);
    painter->setFont(font);
    painter->drawText(textRect,Qt::AlignVCenter | Qt::AlignLeft,DescriName);



    //qInfo("state %08X",option.state);//State_MouseOver

    /*
    QVariant imageData = index.data(Qt::UserRole + 1);
    QPixmap image = imageData.value<QPixmap>();

    painter->drawPixmap(rect,image);
    */

    //QStyledItemDelegate::paint(painter,option,index);
}

QSize MultiListDelegate::sizeHint(const QStyleOptionViewItem &option,const QModelIndex &index) const
{
    QSize s = QStyledItemDelegate::sizeHint(option,index);
    s.setHeight(50);
    return s;
}
