#include "multioperation.h"
#include "ui_multioperation.h"

MultiOperation::MultiOperation(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MultiOperation)
{
    ui->setupUi(this);
}

MultiOperation::~MultiOperation()
{
    delete ui;
}
