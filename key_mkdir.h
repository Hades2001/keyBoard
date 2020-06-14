#ifndef KEY_MKDIR_H
#define KEY_MKDIR_H

#include "virtualkey.h"
#include "virtualpage.h"

class key_mkdir : public VirtualKey
{
public:
    key_mkdir(int type);

public:
    void keypressed(bool) {;}
    void upDatePic(QPixmap) {;}
private:
    virtualPage *_newpage;
};

#endif // KEY_MKDIR_H
