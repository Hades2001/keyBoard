#ifndef VIRTUALKEY_H
#define VIRTUALKEY_H

#include <QObject>
#include <QPixmap>
#include <QPluginLoader>
#include <QList>

class VirtualKey : public QObject
{
    Q_OBJECT

public:
    enum VirtualKeyType{
        kTypeIDLE = 0,
        kTypeDIR,
        kTypeEmptyDIR,
        kTypeBack,
        kTypeCMD,
        kTypeEndpoint,
        kTypeMAX
    };

    enum sysMsgID{
        kMsgIDLE = 0,
        kMsgMkdir,
        kMsgsetPage,
        kMsgsetPageIndex,
        kMsgRemovePage,
        kMsgConfig,
        kMsgMAX
    };

public:
    virtual  ~VirtualKey() {}

public:
    virtual void keypressed(bool) {;}
    virtual void upDatePic(QPixmap) {;}
    virtual void keypressedGUI(){;}
    virtual void keyDoubleClickGUI(){;}
    virtual void revertSystemInfo(QVariant,QVariant){;}
    virtual void createdVirtual(){;}


    virtual QVariant getConfig(){return QJsonObject();}
    virtual void SetConfig(QVariant){;}
signals:
    void sendData(QByteArray);
    void updateGUI(QPixmap pic);
    void sendSystemInfo(QVariant,QVariant);

public:
    typedef struct childImage
    {
        QPixmap childPixmap;
        int     imageID;
        inline childImage(QPixmap image)
        {
            childPixmap = image;
        }
        inline childImage(QString imagePath)
        {
            childPixmap.load(imagePath);
        }
    }Image_t;
    QList<VirtualKey::Image_t> _imageList;

    virtual void setImageList(QList<Image_t> list){

        _imageList = list;
    }

    QString Name;
    QString Title;
    int  type = kTypeIDLE;

    QString parentsName;
    QString childName;

    int     childID = -1;
    int     imageID = -1;

    QWidget *setWidget = nullptr;
    //childImage_t image;

private:
    //QPluginLoader *PluginPtr;
};


#endif // VIRTUALKEY_H
