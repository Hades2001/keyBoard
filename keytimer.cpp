#include "keytimer.h"

KeyTimer::KeyTimer()
{
    //imageID = _imageList[0].imageID;
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


