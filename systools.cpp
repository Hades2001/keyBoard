#include "systools.h"

sysTools::sysTools(QObject *parent)
{
    Q_UNUSED(parent);

    pluginNameStr = "SystemTools";

    metaMap.insert("make_dir", key_mkdir::staticMetaObject);
    metaMap.insert("kTimer", KeyTimer::staticMetaObject);

    childImage_t makedirImage;
    makedirImage.imageList.insert(0,VirtualKey::Image_t(":/icons/icon/dir.png"));
    makedirImage.imageList.insert(1,VirtualKey::Image_t(":/icons/icon/buckdir.png"));
    childImageMap.insert("make_dir",makedirImage);

    childImage_t kTimerImage;
    kTimerImage.imageList.insert(0,VirtualKey::Image_t(":/icons/icon/branch_open.png"));
    childImageMap.insert("kTimer",kTimerImage);

}

