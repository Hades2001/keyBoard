#include "imagesmanage.h"
#include "ui_imagesmanage.h"

ImagesManage::ImagesManage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ImagesManage)
{
    ui->setupUi(this);

    ui->listWidget->verticalScrollBar()->setStyleSheet(QScrollBarQss);

    QList<int> keys = uImageMap.sysImageList.keys();
    ui->listWidget->setIconSize(QSize(60,60));
    ui->listWidget->setViewMode(QListView::IconMode);
    foreach( int id, keys )
    {
        imageMap::imageBox_t imagebox = uImageMap.sysImageList[id];
        QListWidgetItem* item=new QListWidgetItem(imagebox.image,QString("id=%1").arg(id));

        item->setData(Qt::UserRole + 1,id);
        item->setData(Qt::UserRole + 2,imagebox.Attributes);
        ui->listWidget->addItem(item);
    }
    ui->bn_delete->setEnabled(false);
}

ImagesManage::~ImagesManage()
{
    delete ui;
}


int ImagesManage::getImageID()
{
    this->exec();
    return _imageID;
}

void ImagesManage::on_bn_close_pressed()
{
    this->close();
}

void ImagesManage::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    _imageID = item->data(Qt::UserRole + 1).toInt();
    this->close();
}

void ImagesManage::on_listWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    Q_UNUSED(previous);
    _imageID = current->data(Qt::UserRole + 1).toInt();
    ui->bn_image->setIconSize(QSize(100,100));
    ui->bn_image->setIcon(current->icon());

    int Attributes = current->data(Qt::UserRole + 2).toInt();
    if( Attributes != imageMap::kANormal )
    {
        ui->bn_delete->setEnabled(false);
    }
    else
    {
        ui->bn_delete->setEnabled(true);
    }
    _current = current;
}

void ImagesManage::on_bn_add_pressed()
{
    QStringList list =  QFileDialog::getOpenFileNames(this,
                                                      tr("Open Image"),
                                                      "./",
                                                      "Image File (*.png *.jpeg *.jpg *.bmp)");

    if(list.isEmpty()) return;
    foreach( QString name, list )
    {
        QPixmap image = QPixmap(name).scaled(240,240,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
        int id = uImageMap.RegisterImapge(image,imageMap::kANormal);
        QListWidgetItem* item=new QListWidgetItem(image,QString("id=%1").arg(id));
        ui->listWidget->addItem(item);
    }
}

void ImagesManage::on_bn_delete_pressed()
{
    if( _imageID != -1 )
    {
        uImageMap.removePic(_imageID );
        if( ui->listWidget->currentRow() != -1 )
        {
            ui->listWidget->takeItem(ui->listWidget->currentRow());
        }
    }
}