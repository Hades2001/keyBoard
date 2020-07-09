#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QPainter>
#include <QMimeData>
#include <QDrag>
#include <QTreeWidgetItem>
#include <QDir>
#include <QPluginLoader>
#include <QButtonGroup>
#include <QMessageBox>
#include <QListWidget>
#include <QFileDialog>
#include <QPushButton>
#include "nofocusframedelegate.h"
#include "treeitemdelegate.h"
#include "toolsbutton.h"
#include "keyconfig.h"
#include "plugininterface.h"
#include "keytimer.h"
#include "virtualkey.h"
#include "virtualpage.h"
#include "imagesmanage.h"
#include "multioperation.h"

#include "systools.h"
#include "pluginmap.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void flushTreeWidget();
    int getEmptypageIndex();
    virtualPage *creatNewPage(int column, int row, int *index);
    int mkNewpage(int column, int row);
    int mkDirpage(int num, int column, int row);
    int removePage(int pageIndex);

    void saveConfig();
    int readFromConfig();

private:
    Ui::MainWindow *ui;

    QList<QTreeWidgetItem *> items;

    sysTools _systools;
    QMap <int, virtualPage*> pageMap;
    int _CurrentPageIndex = -1;
    int _removePageDeep = 0;

    VirtualKey *_VirtualKeyptr = nullptr;
    QWidget *_nullWidget;
    bool    _configFlag = false;

public slots:
    void sysMsgSlots(int, QVariant,QVariant);

protected:
    void mousePressEvent(QMouseEvent *event);
private slots:
    void on_Bn_Save_pressed();
    void on_bn_image_pressed();
    void on_Bn_ImageManage_pressed();
};

#endif // MAINWINDOW_H
