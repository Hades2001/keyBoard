#ifndef VIRTUALKEY_H
#define VIRTUALKEY_H

#include <QObject>
#include <QPixmap>
#include <QPluginLoader>
#include <QList>
#include <QDebug>
#include <QWidget>

class VirtualKey : public QWidget
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
        kTypeMultiOperation,
        kTypeMAX
    };

    enum sysMsgID{
        kMsgIDLE = 0,
        kMsgMkdir,
        kMsgsetPage,
        kMsgsetPageIndex,
        kMsgRemovePage,
        kMsgConfig,
        kMsgSaveConfig,
        kMsgAddMultiPage,
        kMsgSetMultiPage,
        kMsgRemoveMultiPage,
        kMsgShowKeyPtr,
        kMsgHideKeyPtr,
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

    QString parentDescribeName;
    QString parentDescribeInfo;
    QString DescribeName;
    QString DescribeInfo;

    int     childID = -1;
    int     imageID = -1;

    QWidget *setWidget = nullptr;
    //childImage_t image;

private:
    //QPluginLoader *PluginPtr;
};

Q_DECLARE_METATYPE(VirtualKey*)


#endif // VIRTUALKEY_H
