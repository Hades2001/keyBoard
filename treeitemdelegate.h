#ifndef TREEITEMDELEGATE_H
#define TREEITEMDELEGATE_H

#include <QObject>
#include <QPainter>
#include <QPixmap>
#include <QStyledItemDelegate>
#include <QFontDatabase>
class TreeItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit TreeItemDelegate(QObject *parent = nullptr);
    //void print()

    void paint(QPainter *painter,
               const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    QSize sizeHint(const QStyleOptionViewItem &option,
                   const QModelIndex &index) const override;

signals:

public slots:
};

#endif // TREEITEMDELEGATE_H
