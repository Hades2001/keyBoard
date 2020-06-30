#ifndef KEY_MKDIR_H
#define KEY_MKDIR_H

#include "virtualkey.h"
#include "virtualpage.h"

class key_mkdir : public VirtualKey
{
public:
    key_mkdir();

protected:
    void keypressed(bool) {;}
    void upDatePic(QPixmap) {;}
    void keypressedGUI();
    void keyDoubleClickGUI();
    void revertSystemInfo(QVariant,QVariant);
    void createdVirtual();

private:
    int _pageIndex = -1;
};

#endif // KEY_MKDIR_H
