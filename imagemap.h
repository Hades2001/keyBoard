#ifndef IMAGEMAP_H
#define IMAGEMAP_H

#include <QObject>
#include <QMap>
#include <QPixmap>
#include <QJsonObject>
#include <QJsonArray>

#include "plugininterface.h"
#include "keyconfig.h"
#include "pluginmap.h"

class imageMap : public QObject
{
    Q_OBJECT

public:
    enum{
        kANormal = 0,
        kASysImage ,
        kAReadOnly,
        kAUnUSed,
        kimageAttributesMAX
    }imageAttributes;

    typedef struct imageBox{
        int id;
        QPixmap image;
        int Attributes;
        int usedNumber;
    }imageBox_t;

    QMap<int,imageBox_t> sysImageList;
    //QHash<int,imageBox_t> sysImageList;

public:
    explicit imageMap(QObject *parent = nullptr);
    int findEmptyId();
    int RegisterImapge(QPixmap,int);
    int SetImageToID(int,QPixmap,int);
    QPixmap findImage(int);
    int replaceImage(int,QPixmap,int);
    int removePic(int);
    bool imageIsOperated(){ return _operatedFlag; }
    void cleanoperatedFlag(){ _operatedFlag = false; }
    QJsonObject saveImage();
    int readFromJsonConfig(QJsonObject);

    int readPluginImageFromJson(QJsonObject jsonOBJ);
signals:

public slots:

private:
    bool _operatedFlag = false;

};

extern imageMap uImageMap;

#endif // IMAGEMAP_H
