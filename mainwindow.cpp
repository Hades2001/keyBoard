#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    sysconfig = new keyconfig(this);
    uPulginMap.Map.insert(_systools.pluginName(),&_systools);
    flushTreeWidget();

    /*
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
    */
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
    //qDebug()<<num<<IDprm<<dataprm;

    switch( idNum )
    {
        case VirtualKey::kMsgMkdir:
            mkDirpage(num,4,3);
          break;
        case VirtualKey::kMsgsetPage:
            qDebug()<<"kMsgsetPage"<<dataprm;
            ui->sW_btn->setCurrentWidget(pageMap[dataprm.toInt()]);
            _CurrentPageIndex = dataprm.toInt();
        break;
    default: break;
    }
}

int MainWindow::getEmptypageIndex()
{
    for ( int i = 0; i < 30000; i++) {
        if( pageMap.contains(i) == false )
        {
            return i;
        }
    }
    return -1;
}

int MainWindow::mkNewpage(int column, int row)
{
    int pageIndex = getEmptypageIndex();
    if( pageIndex == -1 ) return -1;

    virtualPage* newpage = new virtualPage(this,column,row);
    newpage->pageIndex = pageIndex;
    connect( newpage,&virtualPage::sendSystemInfo,this,&MainWindow::sysMsgSlots);
    ui->sW_btn->addWidget(newpage);
    pageMap.insert(pageIndex,newpage);
    return pageIndex;
}

int MainWindow::mkDirpage(int num,int column, int row)
{
    int pageIndex = getEmptypageIndex();
    if( pageIndex == -1 ) return -1;

    virtualPage* newpage = new virtualPage(this,column,row);
    newpage->pageIndex = pageIndex;
    VirtualKey* keyback = _systools.getpluginChildPtr(0);
    keyback->parentsName = _systools.pluginName();
    keyback->childID = 0;
    keyback->type = VirtualKey::kTypeBack;
    newpage->setBtnClassPtr(0,keyback);
    newpage->revertSystemInfo(0,0,_CurrentPageIndex);
    connect( newpage,&virtualPage::sendSystemInfo,this,&MainWindow::sysMsgSlots);

    pageMap.insert(pageIndex,newpage);
    ui->sW_btn->addWidget(newpage);
    //pageMap.insert(pageMap.size(),newpage);
    pageMap[_CurrentPageIndex]->revertSystemInfo(num,0,pageIndex);

    return pageIndex;
}

void MainWindow::flushTreeWidget()
{
    items.clear();

    QList<QString> pluginKeyList = uPulginMap.Map.keys();

    foreach ( QString  name, pluginKeyList )
    {
        QTreeWidgetItem* item = new QTreeWidgetItem(ui->treeWidget,QStringList(name));
        item->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled );
        PluginInterface* Plugptr = uPulginMap.Map[name];
        int count = Plugptr->getPluginsNumber();
        for(int i = 0; i < count; i++ )
        {
            QString namechild = Plugptr->getpluginChildName(quint16(i));
            QTreeWidgetItem* itemchild=new QTreeWidgetItem(item,QStringList(namechild));
            itemchild->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsDragEnabled );

            QFont font = this->font();
            font.setPixelSize(16);
            itemchild->setFont(0,font);

            //itemchild1->setIcon(0,QIcon(":/icons/icon/arrow.png"));
            itemchild->setData(1,1,QVariant(name));
            itemchild->setData(0,1,QVariant(i));

        }
        items.append(item);
    }
}

void  MainWindow::saveConfig()
{
    QJsonArray  jsonArray;
    QJsonObject pagejsonOBJ;

    qDebug()<<"Page Size:"<<QString::number(pageMap.size());
    for( int i = 0; i < pageMap.size(); i++ )
    {
        virtualPage *ptr = pageMap[i];
        ptr->revertSystemInfo(-1,VirtualKey::kMsgConfig,QVariant(0));
        QJsonObject jsonOBJ = ptr->generateConfig();
        jsonArray.insert(i,jsonOBJ);

    }
    pagejsonOBJ.insert("pageArray",jsonArray);

    sysconfig->writeJsonDataToConfigFile("page",pagejsonOBJ);
    sysconfig->saveConfig("default");

}
void  MainWindow::readFromConfig()
{
    QJsonObject pageJsonObj = sysconfig->getConfigJsonOBJ();
    if( !pageJsonObj.contains("page"))
    {
        QMessageBox::warning(this,"Config Error","JSON file is damaged");
        return;
    }
    //pageJsonObj["page"]
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

void MainWindow::on_Bn_Save_pressed()
{
    saveConfig();
}

