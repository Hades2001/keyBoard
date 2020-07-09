#ifndef KEYDEFINE_H
#define KEYDEFINE_H

#include <QWidget>
#include <virtualkey.h>

namespace Ui {
class keyDefine;
}

class keyDefine : public VirtualKey
{
    Q_OBJECT

public:
    Q_INVOKABLE explicit keyDefine(QWidget *parent = nullptr);
    ~keyDefine();

protected:

    void keypressed(bool);
    void upDatePic(QPixmap);
    void keypressedGUI();
    void keyDoubleClickGUI();
    void revertSystemInfo(QVariant,QVariant);
    void createdVirtual();

    QVariant getConfig();
    void SetConfig(QVariant);


private slots:
    void on_keySequenceEdit_keySequenceChanged(const QKeySequence &keySequence);

private:
    Ui::keyDefine *ui;
};

#endif // KEYDEFINE_H
