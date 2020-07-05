#ifndef KEYCONFIG_H
#define KEYCONFIG_H

#include <QObject>
#include <QCoreApplication>
#include <QDir>
#include <QSettings>
#include <QDebug>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>


class keyconfig : public QObject
{
    Q_OBJECT
public:
    explicit keyconfig(QObject *parent = nullptr,QString name = "default");
    void creatConfig(QString configName);

    int writeConfigListToFile(QString defauleName = "default");
    int readConfigListFromFile();
    int creatConfigFile(QString name);
    int readConfigFile(QString name);
    int writeDataToConfigFile(QString key,QByteArray data);
    int writeJsonDataToConfigFile(QString key,QVariant data);
    int saveConfig(QString name);
    QString getImagePath(){return _imagePath;}
    QJsonObject getConfigJsonOBJ(){ return _configJsonOBJ;}

private:
    QJsonObject _configJsonOBJ;
    QString _default;
    QString _filepath;
    QString _imagePath;
    QList<QString> _configMap;
signals:

public slots:
};

extern keyconfig *sysconfig;

#endif // KEYCONFIG_H
