#ifndef MULTIOPERATION_H
#define MULTIOPERATION_H

#include <QWidget>

namespace Ui {
class MultiOperation;
}

class MultiOperation : public QWidget
{
    Q_OBJECT

public:
    explicit MultiOperation(QWidget *parent = nullptr);
    ~MultiOperation();

private:
    Ui::MultiOperation *ui;
};

#endif // MULTIOPERATION_H
