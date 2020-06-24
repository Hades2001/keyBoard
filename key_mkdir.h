#ifndef KEY_MKDIR_H
#define KEY_MKDIR_H

#include "virtualkey.h"
#include "virtualpage.h"

class key_mkdir : public VirtualKey
{
public:
    key_mkdir(int type);

protected:
    void keypressed(bool) {;}
    void upDatePic(QPixmap) {;}
    void keypressedGUI(){;}
    void keyDoubleClickGUI(){;}
    void revertSystemInfo(QVariant,QVariant){;}
    void createdVirtual(){;}

signals:
    void sendData(QByteArray);
    void updateGUI(QPixmap pic);
    void sendSystemInfo(QVariant,QVariant);

private:
    virtualPage *_newpage;
};

#endif // KEY_MKDIR_H
