#ifndef KEY_MKDIR_H
#define KEY_MKDIR_H

#include <QJsonObject>
#include "virtualkey.h"
#include "virtualpage.h"

class key_mkdir : public VirtualKey
{
    Q_OBJECT
public:
    Q_INVOKABLE key_mkdir();
protected:
    void keypressed(bool) {;}
    void upDatePic(QPixmap) {;}
    void keypressedGUI();
    void keyDoubleClickGUI();
    void revertSystemInfo(QVariant,QVariant);
    void createdVirtual();

    QVariant getConfig();
    void SetConfig(QVariant);

private:
    int _pageIndex = -1;
};


#endif // KEY_MKDIR_H
