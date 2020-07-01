#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    sysconfig = new keyconfig(this);
    uPluginMap.Register(_systools.pluginName(),&_systools);
    //uPluginMap.Map.insert(_systools.pluginName(),&_systools);
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

    _CurrentPageIndex = mkNewpage(4,3);
    ui->sW_btn->setCurrentIndex(_CurrentPageIndex);
    */
    if( readFromConfig()!= 0)
    {
        _CurrentPageIndex = mkNewpage(4,3);
        ui->sW_btn->setCurrentIndex(_CurrentPageIndex);
        saveConfig();
    }
    else
    {
        ui->sW_btn->setCurrentWidget(pageMap[_CurrentPageIndex]);
    }
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
        case VirtualKey::kMsgMkdir:
            mkDirpage(num,4,3);
          break;
        case VirtualKey::kMsgsetPage:
            qDebug()<<"kMsgsetPage"<<dataprm;
            ui->sW_btn->setCurrentWidget(pageMap[dataprm.toInt()]);
            _CurrentPageIndex = dataprm.toInt();
        break;
        case VirtualKey::kMsgRemovePage:
            qDebug()<<"remove page"<<dataprm;
            removePage(dataprm.toInt());
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
virtualPage* MainWindow::creatNewPage(int column, int row, int* index)
{
    int pageIndex = 0;
    if( *index == -1 )
    {
        pageIndex = getEmptypageIndex();
        if( pageIndex == -1 ) return nullptr;
    }
    else {
        pageIndex = *index;
    }

    virtualPage* newpage = new virtualPage(this,column,row);
    newpage->pageIndex = pageIndex;
    connect( newpage,&virtualPage::sendSystemInfo,this,&MainWindow::sysMsgSlots);
    connect( newpage,&virtualPage::btnpressed,this,[=](int id,VirtualKey *ptr){
        Q_UNUSED(id);
        if( ptr->type == VirtualKey::kTypeDIR || ptr->type == VirtualKey::kTypeEndpoint )
        {
            QPixmap image = uImageMap.findImage(ptr->imageID);
            ui->bn_image->setIconSize(QSize(100,100));
            ui->bn_image->setIcon(image);
        }
    });
    ui->sW_btn->addWidget(newpage);
    pageMap.insert(pageIndex,newpage);

    *index = pageIndex;
    return newpage;
}

int MainWindow::mkNewpage(int column, int row)
{
    int pageIndex = -1;
    creatNewPage(column, row, &pageIndex);
    return pageIndex;
}

int MainWindow::mkDirpage(int num,int column, int row)
{
    int pageIndex = -1;
    virtualPage* newpage = creatNewPage(column, row, &pageIndex);

    VirtualKey *keyback = _systools.creatChildPtr("make_dir");

    keyback->type = VirtualKey::kTypeBack;
    newpage->setBtnClassPtr(0,keyback);
    newpage->revertSystemInfo(0,VirtualKey::kMsgsetPageIndex,_CurrentPageIndex);

    pageMap[_CurrentPageIndex]->revertSystemInfo(num,VirtualKey::kMsgsetPageIndex,pageIndex);

    return pageIndex;
}

int MainWindow::removePage(int pageIndex)
{
    if( pageMap.contains(pageIndex))
    {
        virtualPage* page = pageMap[pageIndex];
        for (int i = 0; i < page->getBtnMaxNumber(); i++) {
            VirtualKey* ptr = page->getBtnClassPtr(i);
            if( ptr->type == VirtualKey::kTypeDIR )
            {
                _removePageDeep ++;
                ptr->type = VirtualKey::kTypeEmptyDIR;
                ptr->revertSystemInfo(VirtualKey::kMsgRemovePage,0);
                return -1;
            }
            else if ( ptr->type == VirtualKey::kTypeEmptyDIR )
            {
                page->removeBtnClassPtr(i);
            }
        }

        if( _removePageDeep != 0 )
        {
            _removePageDeep--;
            VirtualKey* ptr = page->getBtnClassPtr(0);
            if( ptr->type == VirtualKey::kTypeBack )
            {
                ptr->revertSystemInfo(VirtualKey::kMsgRemovePage,0);
            }
        }
        pageMap.remove(pageIndex);
        qInfo("remove %d IndexPade, deep %d",pageIndex,_removePageDeep);

        return 0;
    }
    else
    {
        return -1;
    }
}

void MainWindow::flushTreeWidget()
{
    items.clear();

    QList<QString> pluginKeyList = uPluginMap.Map.keys();

    foreach ( QString  name, pluginKeyList )
    {
        QTreeWidgetItem* item = new QTreeWidgetItem(ui->treeWidget,QStringList(name));
        item->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled );
        PluginInterface* Plugptr = uPluginMap.Map[name];

        QList<QString> childnameList = Plugptr->metaMap.keys();
        foreach( QString childname, childnameList )
        {
            QString namechild = childname;
            QTreeWidgetItem* itemchild=new QTreeWidgetItem(item,QStringList(namechild));
            itemchild->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsDragEnabled );

            QFont font = this->font();
            font.setPixelSize(16);
            itemchild->setFont(0,font);

            //itemchild1->setIcon(0,QIcon(":/icons/icon/arrow.png"));
            itemchild->setData(1,1,QVariant(name));
            itemchild->setData(0,1,QVariant(childname));
        }
        items.append(item);
    }
}

void  MainWindow::saveConfig()
{
    QJsonArray  jsonArray;
    QJsonObject pagejsonOBJ;

    qDebug()<<"Page Size:"<<QString::number(pageMap.size());

    foreach( virtualPage *ptr, pageMap)
    {
        ptr->revertSystemInfo(-1,VirtualKey::kMsgConfig,QVariant(0));
        QJsonObject jsonOBJ = ptr->generateConfig();
        jsonArray.append(jsonOBJ);
    }
    pagejsonOBJ.insert("pageArray",jsonArray);
    pagejsonOBJ.insert("_CurrentPageIndex",_CurrentPageIndex);

    sysconfig->writeJsonDataToConfigFile("page",pagejsonOBJ);
    sysconfig->saveConfig("default");

}
int MainWindow::readFromConfig()
{
    QJsonObject pageJsonObj = sysconfig->getConfigJsonOBJ();
    if( !pageJsonObj.contains("page"))
    {
        QMessageBox::warning(this,"Config Error","JSON file is damaged");
        return -1;
    }
    QJsonObject jsonPageOBJ = pageJsonObj["page"].toObject();

    if( !jsonPageOBJ.contains("_CurrentPageIndex"))
    {
        return -1;
    }
    _CurrentPageIndex = jsonPageOBJ["_CurrentPageIndex"].toInt();

    QJsonArray pageArray = jsonPageOBJ["pageArray"].toArray();
    if( pageArray.size() == 0 )
    {
        QMessageBox::warning(this,"Config Error","Page is Empty");
        return -1;
    }

    for( int i = 0; i < pageArray.size(); i++)
    {
        QJsonObject jsonOBJ = pageArray[i].toObject();

        int pageIndex = jsonOBJ["pageIndex"].toInt();
        QJsonArray jsonArray = jsonOBJ["keyArray"].toArray();

        virtualPage* newpage = creatNewPage(4, 3, &pageIndex);

        newpage->setBtnFromConfigFile(jsonArray);
    }

    return 0;
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

