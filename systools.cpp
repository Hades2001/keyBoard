#include "systools.h"

sysTools::sysTools(QObject *parent)
{
    Q_UNUSED(parent);

    pluginNameStr = "SystemTools";
    pluginIcon = QPixmap(":/icons/icon/systemtools_icon.png");
    DescribeName = QObject::tr("系统工具");

    metaMap.insert("make_dir", key_mkdir::staticMetaObject);
    metaMap.insert("kTimer", KeyTimer::staticMetaObject);

    childImage_t makedirImage;
    makedirImage.DescribeInfo = QObject::tr("创建文件夹");
    makedirImage.DescribeName = QObject::tr("文件夹");
    makedirImage.childIcon = QPixmap(":/icons/icon/adddir_icon.png");
    makedirImage.imageList.insert(0,VirtualKey::Image_t(":/icons/icon/dir.png"));
    makedirImage.imageList.insert(1,VirtualKey::Image_t(":/icons/icon/buckdir.png"));
    childImageMap.insert("make_dir",makedirImage);

    childImage_t kTimerImage;
    kTimerImage.DescribeInfo = QObject::tr("创建定时器");
    kTimerImage.DescribeName = QObject::tr("定时器");
    kTimerImage.childIcon = QPixmap(":/icons/icon/timer_icon.png");
    kTimerImage.imageList.insert(0,VirtualKey::Image_t(":/icons/icon/timer.png"));
    childImageMap.insert("kTimer",kTimerImage);

}

