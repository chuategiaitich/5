#ifndef COMSERIAL_H
#define COMSERIAL_H

#include<QDebug>
#include<QtSerialPort/QSerialPort>
#include<QtSerialPort/QSerialPortInfo>


class comserial
{
public:
    comserial(QSerialPort *myDev);
    ~comserial();

    QStringList ConnectedDevices();

    bool Connect(QString Port, uint32_t bd);
    bool Disconnect(void);

    qint64 Write(const char *cmd);
    QString Read();
    QString Read(int bufferSize);

private:

    QSerialPort *devSerial;

};

#endif // COMSERIAL_H
