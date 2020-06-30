#ifndef VIRTUALKEY_H
#define VIRTUALKEY_H

#include <QObject>
#include <QPixmap>
#include <QPluginLoader>
#include <QList>

typedef struct VirtaulKeyImage
{
    QPixmap pic;
    quint32 addr;
}VirtaulKeyImage_t;

class VirtualKey : public QObject
{
    Q_OBJECT

public:
    enum VirtualKeyType{
        kTypeIDLE = 0,
        kTypeDIR,
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
    QString Name;
    QString Title;
    int  type = kTypeIDLE;

    QString parentsName;
    int     childID = -1;
    int     imageID = -1;

    QList<VirtaulKeyImage_t> picList;
    QWidget *setWidget = nullptr;

private:
    QPluginLoader *PluginPtr;
};


#endif // VIRTUALKEY_H
