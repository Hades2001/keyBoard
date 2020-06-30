#include "keyconfig.h"

keyconfig::keyconfig(QObject *parent,QString name) : QObject(parent)
{
    Q_UNUSED(name);
    readConfigListFromFile();
    readConfigFile(_default);
    /*
    writeDataToConfigFile("name_user","Hades");
    saveConfig(_default);
    */
}

int keyconfig::writeConfigListToFile(QString defauleName)
{
    if( _configMap.empty())
    {
        return -1;
    }

    if( !_configMap.contains(defauleName))
    {
        return -1;
    }

    QString pathstr = QCoreApplication::applicationDirPath();
    QDir configDir(pathstr);
    if( !configDir.exists("config"))
    {
        configDir.mkdir("config");
    }
    configDir.cd("config");

    QFile configList(configDir.path() + "/configlist.json");

    QJsonArray configlist;
    foreach( QString name, _configMap)
    {
        configlist.append(name);
    }
    QJsonObject jsonObj;
    jsonObj.insert("default",defauleName);
    jsonObj.insert("list",configlist);

    QJsonDocument jsonDoc;
    jsonDoc.setObject(jsonObj);

    configList.open(QIODevice::ReadWrite);
    configList.write(jsonDoc.toJson());
    configList.close();

    return 0;
}
int keyconfig::readConfigListFromFile()
{
    QString pathstr = QCoreApplication::applicationDirPath();
    QDir configDir(pathstr);
    if( !configDir.exists("config"))
    {
        _configMap.append("default");
        creatConfigFile("default");
        writeConfigListToFile("default");
    }
    configDir.cd("config");
    QFile configList(configDir.path() + "/configlist.json");
    if( !configList.exists())
    {
        _configMap.append("default");
        creatConfigFile("default");
        writeConfigListToFile("default");
    }
    configList.open(QIODevice::ReadOnly);
    QByteArray jsonbuff = configList.readAll();
    configList.close();

    QJsonParseError json_error;
    QJsonDocument jsonDoc(QJsonDocument::fromJson(jsonbuff, &json_error));

    if( json_error.error != QJsonParseError::NoError )
    {
        return -1;
    }

    QJsonObject rootObj = jsonDoc.object();
    if( rootObj.contains("list"))
    {
        QJsonArray configlist = rootObj["list"].toArray();
        if( configlist.isEmpty()) return -1;

        _configMap.clear();

        for (int i = 0; i < configlist.size(); i++ ) {
            _configMap.append(configlist[i].toString());
            qDebug()<<configlist[i].toString();
        }
    }
    else {
        return -1;
    }

    if( rootObj.contains("default"))
    {
        _default = rootObj["default"].toString();
        qDebug()<<"default name:"<<_default;
    }
    else {
        return -1;
    }

    return 0;
}

int keyconfig::creatConfigFile(QString name)
{
    Q_UNUSED(name);
    QString pathstr = QCoreApplication::applicationDirPath();
    QDir configDir(pathstr);
    configDir.cd("config");
    if( !configDir.exists(name))
    {
        configDir.mkdir(name);
    }
    configDir.cd(name);
    if( !configDir.exists("image"))
    {
        configDir.mkdir("image");
    }

    QString filename = configDir.path() +"/"+ name + ".json";
    QFile readFile(filename);
    readFile.open(QIODevice::ReadWrite);

    QJsonObject json;
    json.insert("name",name);

    QJsonDocument jsonDoc;
    jsonDoc.setObject(json);

    QByteArray jsonFile =  jsonDoc.toJson();
    readFile.write(jsonFile);
    readFile.close();

    return 0;
}
int keyconfig::readConfigFile(QString name)
{
    if( !_configMap.contains(name))
    {
        return -1;
    }

    QString pathstr = QCoreApplication::applicationDirPath();
    QDir configDir(pathstr);
    configDir.cd("config");
    if( !configDir.exists(name))
    {
        return -1;
    }
    configDir.cd(name);
    if( !configDir.exists("image"))
    {
        return -1;
    }

    QFile configList(configDir.path() +"/"+ name + ".json");
    if( !configList.exists())
    {
        return -1;
    }

    configList.open(QIODevice::ReadOnly);
    QByteArray jsonbuff = configList.readAll();
    configList.close();

    QJsonParseError json_error;
    QJsonDocument jsonDoc(QJsonDocument::fromJson(jsonbuff, &json_error));

    if( json_error.error != QJsonParseError::NoError )
    {
        return -1;
    }

    _configJsonOBJ = jsonDoc.object();

    return 0;
}

int keyconfig::writeDataToConfigFile(QString key,QByteArray data)
{
    if(_configJsonOBJ.contains(key))
    {
        _configJsonOBJ[key] = QString(data);
    }
    else
    {
        _configJsonOBJ.insert(key, QString(data));
    }
    return 0;
}

int keyconfig::writeJsonDataToConfigFile(QString key,QVariant data)
{
    QJsonObject jsonOBJ = data.toJsonObject();
    if(_configJsonOBJ.contains(key))
    {
        _configJsonOBJ[key] = jsonOBJ;
    }
    else
    {
        _configJsonOBJ.insert(key, jsonOBJ);
    }
    return 0;
}


int keyconfig::saveConfig(QString name)
{
    if( !_configMap.contains(name))
    {
        return -1;
    }

    QString pathstr = QCoreApplication::applicationDirPath();
    QDir configDir(pathstr);
    configDir.cd("config");
    if( !configDir.exists(name))
    {
        return -1;
    }
    configDir.cd(name);
    if( !configDir.exists("image"))
    {
        return -1;
    }

    QFile configList(configDir.path() +"/"+ name + ".json");
    if( !configList.exists())
    {
        return -1;
    }

    QJsonDocument jsonDoc;
    jsonDoc.setObject(_configJsonOBJ);

    configList.open(QIODevice::WriteOnly);
    configList.write(jsonDoc.toJson());
    configList.close();

    return 0;
}

keyconfig *sysconfig;
