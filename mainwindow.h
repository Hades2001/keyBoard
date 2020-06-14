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
#include "toolsbutton.h"
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

private:
    Ui::MainWindow *ui;

    sysTools _systools;

protected:
    void mousePressEvent(QMouseEvent *event);
};

#endif // MAINWINDOW_H
