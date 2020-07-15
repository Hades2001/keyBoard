#ifndef KEYMULTIOPERA_H
#define KEYMULTIOPERA_H

#include <QWidget>
#include <QObject>
#include <virtualkey.h>
#include <QListWidget>

#include "multioperation.h"
#include "nofocusframedelegate.h"


namespace Ui {
class keyMultiOpera;
}

class keyMultiOpera : public VirtualKey
{
    Q_OBJECT

public:
    Q_INVOKABLE explicit keyMultiOpera(QWidget *parent = nullptr);
    ~keyMultiOpera();

protected:
    void keypressed(bool);
    void upDatePic(QPixmap);
    void keypressedGUI();
    void keyDoubleClickGUI();
    void revertSystemInfo(QVariant,QVariant);
    void createdVirtual();

    QVariant getConfig();
    void SetConfig(QVariant);

    void setEnabledfromFlag();


private:
    Ui::keyMultiOpera *ui;
    MultiOperation *_MultiOperationPagePtr = nullptr;
    int _parentIndex = -1;
};

#endif // KEYMULTIOPERA_H
