#ifndef SERIALSOCKET_H
#define SERIALSOCKET_H

#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>

class SerialSocket : public QObject
{
    Q_OBJECT
public:
    explicit SerialSocket(QObject *parent = nullptr);

    enum {
        kFSMIDLE = 0,
        kFSMHead,
        kFSMDir,
        kFSMLength,
        kFSMCmd,
        kFSMData,
        kFSMCheck,
        kFSMEnd,
        kFSMMax,
    }uartFSM_e;

    enum {
        kErrorNo = 0,
        kErrorLenghtOutSize,
        kErrorCheckByteFailing,
        kErrorUnFindEndFailing,
        kErrorCmdNoFind,
        kErrorSectorOutSize,
        kErrorMAX,
    }HMI_error;

    typedef struct {
        quint8      dir;
        quint32     length;
        quint8      cmd;
        QByteArray  data;
        quint8      CheckData;
    }UartPact_t;

    typedef struct
    {
        uint8_t FSM;
        int error;
        uint8_t flag;
        UartPact_t Pack;
    }HMIPact_t;

signals:

public slots:
    void serialReadready();
private:
    QSerialPort* _serial;
};

#endif // SERIALSOCKET_H
