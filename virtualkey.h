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

public slots:
    virtual void keypressed(bool) {;}
    virtual void upDatePic(QPixmap) {;}

signals:
    void sendData(QByteArray);
    void updateGUI(QPixmap pic);

public:
    QString Name;
    QString Title;
    VirtualKeyType  type = kTypeIDLE;
    QList<VirtaulKeyImage_t> picList;
    QWidget *setWidget;

private:
    QPluginLoader *PluginPtr;
};

typedef struct VirtualKeyGroup
{
    quint16 column;
    quint16 row;
    VirtualKey *key;

}VirtualKeyGroup_t;

#endif // VIRTUALKEY_H
