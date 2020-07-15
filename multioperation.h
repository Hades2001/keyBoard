#ifndef MULTIOPERATION_H
#define MULTIOPERATION_H

#include <QWidget>

#include "treeitemdelegate.h"
#include "multilistdelegate.h"
#include "virtualkey.h"
#include "nofocusframedelegate.h"

namespace Ui {
class MultiOperation;
}

class MultiOperation : public QWidget
{
    Q_OBJECT

public:
    explicit MultiOperation(QWidget *parent = nullptr);
    ~MultiOperation();

private slots:
    void on_bn_return_pressed();

signals:
    void backToParent();
    void pressVirtual(VirtualKey*);

private:
    Ui::MultiOperation *ui;

};

Q_DECLARE_METATYPE(MultiOperation*)

#endif // MULTIOPERATION_H
