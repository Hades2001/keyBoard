#ifndef KEYTIMER_H
#define KEYTIMER_H

#include <QObject>
#include <QWidget>
#include <virtualkey.h>

class KeyTimer : public VirtualKey
{
    Q_OBJECT
public:
    Q_INVOKABLE KeyTimer();
protected:
    void keypressed(bool);
    void upDatePic(QPixmap);
    void createdVirtual()
    {
        imageID = _imageList[0].imageID;
    }
};

#endif // KEYTIMER_H
