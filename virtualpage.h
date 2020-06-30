#ifndef VIRTUALPAGE_H
#define VIRTUALPAGE_H

#include <QWidget>
#include <QButtonGroup>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

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
    explicit virtualPage(QWidget *parent = nullptr,int column = 4, int row = 3);
    explicit virtualPage(QWidget *parent,int column, int row, QJsonArray json);
    ~virtualPage();

public:
    void creatPage();
    void setBtnClassPtr(int,VirtualKey *);
    void revertSystemInfo(int, QVariant,QVariant);
    void sendSystemInfoToAll(QVariant,QVariant);
    QJsonObject generateConfig();
    int creatPageFromConfigFile(QJsonArray);
    int setBtnFromConfigFile(QJsonArray);

public slots:
    void sendInfo(int id, QVariant pid,QVariant pdata);

private:
    Ui::virtualPage *ui;

public:
    int pageIndex;

private:
    int _column = 4;
    int _row = 3;
    QButtonGroup *_btnGroup;
signals:
    void sendData(int, QByteArray);
    void sendSystemInfo(int, QVariant,QVariant);
};

#endif // VIRTUALPAGE_H
