#include "serialsocket.h"

SerialSocket::SerialSocket(QObject *parent) : QObject(parent)
{
    _serial = new QSerialPort();

    connect(_serial,&QSerialPort::readyRead,this,&SerialSocket::serialReadready,Qt::AutoConnection);
    connect(_serial,&QSerialPort::errorOccurred,this,[=](QSerialPort::SerialPortError error){
        if( error == QSerialPort::ResourceError)
        {
            _serial->close();
            //ui->bn_connect->setText("connect");
            //_dataPack.DataFSM = kIDLE;
            //QMessageBox::warning(this,"Serial Error","ResourceError");
            //scanSerialName();
        }
    },Qt::AutoConnection);
}

void SerialSocket::serialReadready()
{
    QByteArray dataArray = _serial->readAll();
    quint8 data = 0;
    if( dataArray.size() <= 0 ) return;

    for( int i = 0; i < dataArray.size(); i++ )
    {
        data = quint8(dataArray.at(i)) & 0xff;
        /*
        switch( _dataPack.DataFSM )
        {
            case kIDLE:  _dataPack.DataFSM = ( data == 0xAA ) ? kPack : kIDLE; break;
            case kPack: _dataPack.DataFSM = ( data == 0x55 ) ? kpackZ : kIDLE; break;
            case kpackZ:
                if( data == 0x00 )
                {
                    _dataPack.XORData = 0x00 ^ 0xAA ^ 0x55;
                    _dataPack.DataFSM = kLength;
                    _dataPack.count = 0;
                    _dataPack.Length = 0;
                }
                else
                {
                    _dataPack.DataFSM = kIDLE;
                }
                break;
            case kLength:
                _dataPack.Length = ( _dataPack.Length * 256 ) + data;
                _dataPack.XORData ^= data;
                _dataPack.count ++;
                if( _dataPack.count >= 3 )
                {
                    qInfo("Length : %d",_dataPack.Length);
                    _dataPack.DataFSM = kCMD;
                    _dataPack.count = 0;
                }
                break;
            case kCMD:
                _dataPack.CMD = data;
                _dataPack.XORData ^= data;
                qInfo("CMD : %02X",_dataPack.CMD);
                if( _dataPack.CMD == 0x00 )
                {
                    _dataPack.Length --;
                    _dataPack.DataFSM = kData;
                    _dataPack.DataArray.clear();
                    _dataPack.count = 0;
                }
                else
                {
                    _dataPack.DataFSM = kIDLE;
                }
                break;
            case kData:
                _dataPack.DataArray.append(char(data));
                _dataPack.XORData ^= data;
                _dataPack.count ++;
                if( _dataPack.count >= ( _dataPack.Length - 1 ) )
                {
                    _dataPack.DataFSM = kEnd;
                }
                break;
            case kEnd:
                if( _dataPack.XORData == data )
                {
                    qInstallMessageHandler(JPEGMessageOutput);

                    _dataPack.image.loadFromData(_dataPack.DataArray);
                    qInstallMessageHandler(nullptr);

                    if( JPEGCorruptFlag == 0 )
                    {
                        emit sendImage(_dataPack.image);
                    }

                    JPEGCorruptFlag = 0;
                }

                //qDebug()<<"sendImage";
                //qInfo(" data Length : %d",_dataPack.DataArray.size());
                //qInfo(" image w:%d h:%d",_dataPack.image.height(),_dataPack.image.width());

                _dataPack.DataFSM = kIDLE;
                break;
            default: _dataPack.DataFSM = kIDLE; break;
        }
        */
    }
}
