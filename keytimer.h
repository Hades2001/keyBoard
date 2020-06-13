#ifndef KEYTIMER_H
#define KEYTIMER_H

#include <QObject>
#include <QWidget>
#include <virtualkey.h>

class KeyTimer : public VirtualKey
{
public:
    KeyTimer();
protected:
    void keypressed(bool);
    void upDatePic(QPixmap);
};

#endif // KEYTIMER_H
