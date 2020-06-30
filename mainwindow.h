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
#include "toolsbutton.h"
#include "keyconfig.h"
#include "plugininterface.h"
#include "keytimer.h"
#include "virtualkey.h"
#include "virtualpage.h"

#include "systools.h"
#include "pulginmap.h"


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
    int mkNewpage(int column, int row);
    int mkDirpage(int num, int column, int row);

    void saveConfig();
    void readFromConfig();

private:
    Ui::MainWindow *ui;

    QList<QTreeWidgetItem *> items;

    sysTools _systools;
    QMap <int, virtualPage*> pageMap;
    int _CurrentPageIndex = -1;

public slots:
    void sysMsgSlots(int, QVariant,QVariant);

protected:
    void mousePressEvent(QMouseEvent *event);
private slots:
    void on_Bn_Save_pressed();
};

#endif // MAINWINDOW_H
