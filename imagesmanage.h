#ifndef IMAGESMANAGE_H
#define IMAGESMANAGE_H

#include <QDialog>
#include "imagemap.h"
#include <QListWidgetItem>
#include <QScrollBar>
#include <QFileDialog>

namespace Ui {
class ImagesManage;
}

class ImagesManage : public QDialog
{
    Q_OBJECT
public:
    explicit ImagesManage(QWidget *parent = nullptr);
    ~ImagesManage();
    int getImageID();

private slots:
    void on_bn_close_pressed();

    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

    void on_listWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

    void on_bn_add_pressed();

    void on_bn_delete_pressed();

private:
    Ui::ImagesManage *ui;
private:
    int _imageID = -1;
    QListWidgetItem *_current = nullptr;

    QString QScrollBarQss = {"QScrollBar:vertical {\
                   border: none;\
                   background-color: transparent;\
                   width: 10px;\
                   margin: 0px 0 0px 0;\
               }\
               QScrollBar::handle:vertical {\
                   background-color: rgb(255, 200, 0);\
                   min-height: 20px;\
                   border-radius: 5px;\
                   border: none;\
               }\
               QScrollBar::add-line:vertical {\
                   border: 0px solid grey;\
                   background: transparent;\
                   height: 0px;\
                   subcontrol-position: bottom;\
                   subcontrol-origin: margin;\
               }\
               QScrollBar::sub-line:vertical {\
                   border: 0px solid grey;\
                   background: transparent;\
                   height: 0px;\
                   subcontrol-position: top;\
                   subcontrol-origin: margin;\
               }\
               QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {\
                   background: none;\
                   width: 0px;\
                   height: 0px;\
               }"};
};

#endif // IMAGESMANAGE_H
