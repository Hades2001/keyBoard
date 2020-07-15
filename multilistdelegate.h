#ifndef MULTILISTDELEGATE_H
#define MULTILISTDELEGATE_H

#include <QObject>
#include <QPainter>
#include <QPixmap>
#include <QDebug>
#include <QStyledItemDelegate>
#include <QFontDatabase>

class MultiListDelegate : public QStyledItemDelegate
{
public:
    explicit MultiListDelegate(QObject *parent = nullptr);

    void paint(QPainter *painter,
               const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    QSize sizeHint(const QStyleOptionViewItem &option,
                   const QModelIndex &index) const override;

};

#endif // MULTILISTDELEGATE_H
