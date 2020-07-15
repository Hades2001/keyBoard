#include "multioperation.h"
#include "ui_multioperation.h"

MultiOperation::MultiOperation(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MultiOperation)
{
    ui->setupUi(this);
    ui->listWidget->setItemDelegate( new MultiListDelegate );
    ui->listWidget->setGeometry(0,0,this->width(),this->height());
    this->setMinimumSize(5*110 - 10,4*110 - 10);

}

MultiOperation::~MultiOperation()
{
    delete ui;
}

void MultiOperation::on_bn_return_pressed()
{
    emit backToParent();
}

