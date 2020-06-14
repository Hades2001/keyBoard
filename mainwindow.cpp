#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QList<QTreeWidgetItem *> items;

    QTreeWidgetItem* item1=new QTreeWidgetItem(ui->treeWidget,QStringList(QString("123")));
    QTreeWidgetItem* item2=new QTreeWidgetItem(ui->treeWidget,QStringList(QString("123")));
    item1->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled );
    item2->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled );

    QTreeWidgetItem* itemchild1=new QTreeWidgetItem(item2,QStringList(QString("123-1")));
    itemchild1->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsDragEnabled );
    //itemchild1->setIcon(0,QIcon(":/icons/icon/left arrow, file left, left, document, send, arrow.png"));
    itemchild1->setData(0,1,QVariant(10));

    QTreeWidgetItem* itemchild2=new QTreeWidgetItem(item2,QStringList(QString("123-2")));
    itemchild2->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsDragEnabled );
    itemchild2->setData(0,1,QVariant(20));

    QFont font = this->font();
    font.setPixelSize(10);
    itemchild1->setFont(0,font);
    itemchild2->setFont(0,font);

    items.append(item1);
    items.append(item2);

    ui->treeWidget->addTopLevelItems(items);

    uPulginMap.Map.insert(_systools.pluginName(),&_systools);

    QDir dir;
    dir.setPath("E:/Hades_Work/LCD_KEY/qt/keyBoard/plugins");
    if( !dir.exists())
    {
        qWarning("cannot find path %s",qPrintable(dir.path()));
    }
    else
    {
        foreach(QString filename, dir.entryList(QDir::Files)) //遍历path路径下所有文件
        {
            QPluginLoader *loader = new QPluginLoader(dir.absoluteFilePath(filename));

            if (!loader->load()) //过滤掉不是插件的文件
            {
                qWarning("%s is not a plugin",qPrintable(dir.absoluteFilePath(filename)));

                continue;
            }

            QObject *obj = loader->instance();
            PluginInterface *plugin = qobject_cast<PluginInterface *>(obj);

            uPulginMap.Map.insert(plugin->pluginName(),plugin);

            quint16 num = plugin->getPluginsNumber();
            qInfo("Number of Plugin %d",num);
            for( quint16 i = 0; i < num; i++ )
            {
                //qDebug()<<plugin->getpluginChildPtr(i)->Name;
            }
            //ui->scrollArea->setWidget(plugin->getpluginChildPtr(0)->setWidget);
        }
    }

    _CurrentPageIndex = mkNewpage(4,3);
    ui->sW_btn->setCurrentIndex(_CurrentPageIndex);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::sysMsgSlots(int num, QVariant IDprm, QVariant dataprm)
{
    Q_UNUSED(num);
    int idNum = IDprm.toInt();

    switch( idNum )
    {
        case kMsgMkdir:
            //_systools.getpluginChildPtr(0);
            //newPage->setBtnClassPtr();
          break;
        case kMsgsetPage:
            ui->sW_btn->setCurrentIndex(dataprm.toInt());
        break;
    default: break;
    }
}

int MainWindow::mkNewpage(int column, int row)
{
    virtualPage* newpage = new virtualPage(this,column,row);
    connect( newpage,&virtualPage::sendSystemInfo,this,&MainWindow::sysMsgSlots);
    ui->sW_btn->addWidget(newpage);
    pageMap.insert(pageMap.size(),newpage);
    return pageMap.size() - 1;
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event)
    /*
    Q_UNUSED(event);
    qDebug()<<__LINE__;
    QLabel *child = static_cast<QLabel*>(childAt(event->pos()));
    if( child == nullptr ) return;

    qDebug()<<__LINE__;
    QPixmap pixmap = *child->pixmap();

    qDebug()<<__LINE__;
    QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);
    dataStream << pixmap << QPoint(event->pos() - child->pos());
//! [1]

//! [2]
    QMimeData *mimeData = new QMimeData;
    mimeData->setData("application/x-dnditemdata", itemData);
//! [2]

//! [3]
    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    drag->setPixmap(pixmap);
    drag->setHotSpot(event->pos() - child->pos());

    QPixmap tempPixmap = pixmap;

    child->setPixmap(tempPixmap);

    if (drag->exec(Qt::CopyAction | Qt::MoveAction, Qt::CopyAction) == Qt::MoveAction) {
        child->close();
    } else {
        child->show();
        child->setPixmap(pixmap);
    }
    */
}
