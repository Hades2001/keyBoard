#ifndef KEYEXEC_H
#define KEYEXEC_H

#include <QWidget>
#include <QObject>
#include <QJsonObject>
#include <QLineEdit>
#include "virtualkey.h"
#include "virtualpage.h"

namespace Ui {
class keyExec;
}

class keyExec : public VirtualKey
{
    Q_OBJECT
public:
    Q_INVOKABLE keyExec();
    ~keyExec();

protected:
    void keypressed(bool);
    void upDatePic(QPixmap);
    void keypressedGUI();
    void keyDoubleClickGUI();
    void revertSystemInfo(QVariant,QVariant);
    void createdVirtual();

    QVariant getConfig();
    void SetConfig(QVariant);
};

#endif // KEYEXEC_H

///Users/chaoxuanzhe/qt/Lcdkeyboard/keyBoard/keyexec.h:34: warning: Class keyExec inherits from two QObject subclasses QWidget and VirtualKey. This is not supported!
