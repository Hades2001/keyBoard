#ifndef VIRTUALPAGE_H
#define VIRTUALPAGE_H

#include <QWidget>
#include <QButtonGroup>

#include "toolsbutton.h"
#include "plugininterface.h"
#include "keytimer.h"
#include "virtualkey.h"

namespace Ui {
class virtualPage;
}

class virtualPage : public QWidget
{
    Q_OBJECT

public:
    explicit virtualPage(QWidget *parent = nullptr);
    explicit virtualPage(QWidget *parent = nullptr,quint16 column = 4, quint16 row = 3);
    ~virtualPage();

public:
    void creatPage();
    void setBtnClassPtr(int,VirtualKey *);

private:
    Ui::virtualPage *ui;

public:
    int pageIndex;

private:
    quint16 _column = 4;
    quint16 _row = 3;
    QButtonGroup *_btnGroup;

signals:
    void sendData(int, QByteArray);
    void sendSystemInfo(int, QVariant,QVariant);
};

#endif // VIRTUALPAGE_H
