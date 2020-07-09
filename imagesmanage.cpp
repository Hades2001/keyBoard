#include "imagesmanage.h"
#include "ui_imagesmanage.h"

ImagesManage::ImagesManage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ImagesManage)
{
    ui->setupUi(this);

    ui->listWidget->verticalScrollBar()->setStyleSheet(QScrollBarQss);
}

ImagesManage::~ImagesManage()
{
    delete ui;
}

void ImagesManage::flushIconWidget()
{
    int count = ui->listWidget->count();

    for ( int i = 0; i < count; i++ ) {
        QListWidgetItem* ptr = ui->listWidget->item(i);
        delete  ptr;
    }

    ui->listWidget->clear();

    QList<int> keys = uImageMap.sysImageList.keys();
    ui->listWidget->setIconSize(QSize(60,60));
    ui->listWidget->setViewMode(QListView::IconMode);
    ui->listWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);
    foreach( int id, keys )
    {
        imageMap::imageBox_t imagebox = uImageMap.sysImageList[id];
        QListWidgetItem* item=new QListWidgetItem(imagebox.image,QString("id=%1").arg(id));
        item->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled );

        item->setData(Qt::UserRole + 1,id);
        item->setData(Qt::UserRole + 2,imagebox.Attributes);
        ui->listWidget->addItem(item);
    }
    ui->bn_delete->setEnabled(false);
}

int ImagesManage::getImageID()
{
    flushIconWidget();
    this->exec();
    return _imageID;
}

void ImagesManage::checkBtnState()
{
    QList<QListWidgetItem *> list = ui->listWidget->selectedItems();
    if( list.size() > 1 )
    {
        ui->bn_choose->setEnabled(false);
    }
    else if( list.size() == 1 )
    {
        ui->bn_choose->setEnabled(true);
        QListWidgetItem* item = list.at(0);
        int Attributes = item->data(Qt::UserRole + 2).toInt();
        if( Attributes != imageMap::kANormal )
        {
            ui->bn_delete->setEnabled(false);
        }
        else
        {
            ui->bn_delete->setEnabled(true);
        }
    }
    else
    {
        ui->bn_delete->setEnabled(false);
    }
}

void ImagesManage::removeImages()
{
    QList<QListWidgetItem *> list = ui->listWidget->selectedItems();
    if( list.size() >= 1 )
    {
        foreach( QListWidgetItem * item, list )
        {
            int imageID = item->data(Qt::UserRole + 1).toInt();
            int Attributes = item->data(Qt::UserRole + 2).toInt();
            if( Attributes == imageMap::kANormal )
            {
                uImageMap.removePic(imageID );
                int SelectedRow = ui->listWidget->row(item);
                if( SelectedRow != -1 )
                {
                    ui->listWidget->takeItem(SelectedRow);
                    delete item;
                }
            }
        }
    }
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

    QList<QListWidgetItem *> list = ui->listWidget->selectedItems();
    if( list.size() == 1 )
    {
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
        uImageMap.RegisterImapge(image,imageMap::kANormal);
    }

    flushIconWidget();
}

void ImagesManage::on_bn_delete_pressed()
{
    removeImages();
}

void ImagesManage::on_listWidget_itemSelectionChanged()
{
    QList<QListWidgetItem *> list = ui->listWidget->selectedItems();
    if( list.size() > 1 )
    {
        ui->bn_choose->setEnabled(false);
    }
    else if( list.size() == 1 )
    {
        ui->bn_choose->setEnabled(true);
    }
    else
    {
        ui->bn_delete->setEnabled(false);
    }
}

void ImagesManage::keyPressEvent(QKeyEvent *event)
{
    if ( event->type() == QEvent::KeyPress )
    {
        if(( event->key() == Qt::Key_Delete )||( event->key() == Qt::Key_Backspace ))
        {
            qDebug()<<"Delete";
            removeImages();
        }
    }
}
