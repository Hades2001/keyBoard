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
#include "treemodel.h"
#include "toolsbutton.h"
#include "plugininterface.h"
#include "keytimer.h"
#include "virtualkey.h"
#include "virtualpage.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    TreeModel* mModel;
    QMap <QString, QPluginLoader *> _pulginLoaderMap;

protected:
    void mousePressEvent(QMouseEvent *event);
};

#endif // MAINWINDOW_H
