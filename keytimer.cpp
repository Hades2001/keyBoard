#include "keytimer.h"

KeyTimer::KeyTimer()
{
    VirtaulKeyImage_t *picdef = new VirtaulKeyImage_t;
    picdef->pic.load(":/icons/icon/branch_open.png");
    picList.append(*picdef);
    type = kTypeEndpoint;
}

void KeyTimer::keypressed(bool state)
{
    qInfo("keypressed in keytimer");
    Q_UNUSED(state)
}

void KeyTimer::upDatePic(QPixmap Pic)
{
    qInfo("upDatePic in keytimer");
    Q_UNUSED(Pic)
}

