#ifndef PLUGININTERFACE_H
#define PLUGININTERFACE_H

#include <QObject>
#include <QString>
#include <QPixmap>

#include <virtualkey.h>

class PluginInterface
{
public:
    virtual ~PluginInterface(){}

    virtual QString pluginName() = 0;
    virtual VirtualKey* creatChildPtr(QString name)
    {
        VirtualKey *VirtualKeyptr = static_cast<VirtualKey*>(metaMap[name].newInstance());
        VirtualKeyptr->parentsName = pluginNameStr;
        VirtualKeyptr->childName = name;

        VirtualKeyptr->DescribeName = childImageMap[name].DescribeName;
        VirtualKeyptr->DescribeInfo = childImageMap[name].DescribeInfo;

        VirtualKeyptr->parentDescribeName = DescribeName;
        VirtualKeyptr->parentDescribeInfo = DescribeInfo;

        VirtualKeyptr->setImageList(childImageMap[name].imageList);
        return VirtualKeyptr;
    }

    QMap<QString, QMetaObject> metaMap;

public:

    QPixmap pluginIcon;
    QString DescribeName;
    QString DescribeInfo;

    typedef struct
    {       
        QPixmap childIcon;
        QList<VirtualKey::Image_t> imageList;
        QString DescribeName;
        QString DescribeInfo;
    }childImage_t;

    QMap<QString,childImage_t> childImageMap;

    QString pluginNameStr;

signals:
    void sendData(QByteArray);

private:
    //QMap<QString, QMetaObject> metaMap;

};

QT_BEGIN_NAMESPACE

#define Interface_iid "HadesPlugin.Interface"
Q_DECLARE_INTERFACE(PluginInterface, Interface_iid)

QT_END_NAMESPACE

#endif // PLUGININTERFACE_H
