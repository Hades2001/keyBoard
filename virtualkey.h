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
        kTypeCMD,
        kTypeEndpoint,
        kTypeMAX
    };

public:
    virtual  ~VirtualKey() {}

public:
    virtual void keypressed(bool) {;}
    virtual void upDatePic(QPixmap) {;}
    virtual void keypressedGUI(){;}
    virtual void keyDoubleClickGUI(){;}
    virtual void revertSystemInfo(QVariant,QVariant);

signals:
    void sendData(QByteArray);
    void updateGUI(QPixmap pic);
    void sendSystemInfo(QVariant,QVariant);

public:
    QString Name;
    QString Title;
    VirtualKeyType  type = kTypeIDLE;
    QList<VirtaulKeyImage_t> picList;
    QWidget *setWidget = nullptr;

private:
    QPluginLoader *PluginPtr;
};


#endif // VIRTUALKEY_H
