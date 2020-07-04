#include "keyexec.h"
#include "ui_keyexec.h"

keyExec::keyExec(QWidget *parent) :
    ui(new Ui::keyExec)
{
    Q_UNUSED(parent);
    ui->setupUi(this);
    setWidget = this;
    type = kTypeEndpoint;

    ui->lineEdit->setEnabled(true);
    ui->pushButton->setEnabled(true);
    ui->lineEdit_2->setEnabled(false);
    ui->radioButton->setChecked(true);
    _choose_flag = 0;
}

keyExec::~keyExec()
{
    delete ui;
}

void keyExec::keypressed(bool)
{

}
void keyExec::upDatePic(QPixmap)
{

}
void keyExec::keypressedGUI()
{

}
void keyExec::keyDoubleClickGUI()
{
    /*
    qInfo("keyDoubleClickGUI");
    if(_choose_flag == 0 )
    {
        if(_execPath.isEmpty())return;
        _Process->start(_execPath);
    }
    else
    {
        if(_shellPath.isEmpty())return;
        _Process->start("ping 120.24.58.30");
    }
    if (!_Process->waitForStarted())
        {
           QMessageBox::warning(this,
                                tr("错误"),
                                tr("运行错误"));
        }
    */
}

void keyExec::revertSystemInfo(QVariant,QVariant){}
void keyExec::createdVirtual()
{
    imageID = _imageList[0].imageID;
}

QVariant keyExec::getConfig()
{
    QJsonObject jsonObject;
    jsonObject.insert("flag",_choose_flag);
    jsonObject.insert("execPath",_execPath);
    jsonObject.insert("shellPath",_shellPath);

    return jsonObject;
}

void keyExec::SetConfig(QVariant data)
{
    QJsonObject jsonObject = data.toJsonObject();
    _choose_flag = jsonObject["flag"].toInt();
    _execPath = jsonObject["execPath"].toString();
    _shellPath = jsonObject["shellPath"].toString();
    ui->lineEdit->setText(_execPath);
    ui->lineEdit_2->setText(_shellPath);
    if(_choose_flag == 0 )
    {
        ui->radioButton->setChecked(true);
    }
    else
    {
        ui->radioButton_2->setChecked(true);
    }
    setEnabledfromFlag();
}

void keyExec::setEnabledfromFlag()
{
    if(_choose_flag == 0 )
    {
        ui->lineEdit->setEnabled(true);
        ui->pushButton->setEnabled(true);
        ui->lineEdit_2->setEnabled(false);
    }
    else
    {
        ui->lineEdit->setEnabled(false);
        ui->pushButton->setEnabled(false);
        ui->lineEdit_2->setEnabled(true);
    }
    emit sendSystemInfo(kMsgSaveConfig,0);
}

void keyExec::on_radioButton_clicked(bool checked)
{
    if(checked)
    {
        _choose_flag = 0;
    }
    else
    {
        _choose_flag = 1;
    }
    setEnabledfromFlag();
}

void keyExec::on_radioButton_2_clicked(bool checked)
{
    if(!checked)
    {
        _choose_flag = 0;
    }
    else
    {
        _choose_flag = 1;
    }
    setEnabledfromFlag();
}

void keyExec::on_lineEdit_2_textChanged(const QString &arg1)
{
    _shellPath = arg1;
    emit sendSystemInfo(kMsgSaveConfig,0);
}

void keyExec::on_pushButton_pressed()
{
   QString filePath = QFileDialog::getOpenFileName(this,
                                    tr("选择运行的文件"),
                                    "./",
                                    "All File (*.*)");
   if(filePath.isEmpty()) return;
   _execPath = filePath;
   ui->lineEdit->setText(_execPath);
   emit sendSystemInfo(kMsgSaveConfig,0);
}

void keyExec::printResult(int,QProcess::ExitStatus)
{
    qDebug()<<"output:"<<QString::fromLocal8Bit(_Process->readAllStandardOutput());
}
