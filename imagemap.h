#ifndef IMAGEMAP_H
#define IMAGEMAP_H

#include <QObject>
#include <QMap>
#include <QPixmap>

class imageMap : public QObject
{
    Q_OBJECT
public:
    explicit imageMap(QObject *parent = nullptr);
    int findEmptyId();
    int RegisterImapge(QPixmap);
    QPixmap findImage(int);
signals:

public slots:

public:
    QMap<int,QPixmap> sysImageList;
};

extern imageMap uImageMap;

#endif // IMAGEMAP_H
