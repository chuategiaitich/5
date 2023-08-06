#include "comserial.h"

comserial::comserial(QSerialPort *myDev)
{
    devSerial = myDev;
}
QStringList comserial::ConnectedDevices(){
    QStringList devs;

    foreach (const QSerialPortInfo info,QSerialPortInfo::availablePorts()){

        devSerial->setPort(info);
        if(devSerial->open(QIODeviceBase::ReadWrite))
        {
            devSerial->close();
            devs << info.portName();
        }
    }
    return devs;
}

bool comserial::Connect(QString port, uint32_t bd){

    devSerial->setPortName(port);

    switch (bd) {
    case 2400:
        devSerial->setBaudRate(QSerialPort::Baud2400);
        break;

    case 4800:
        devSerial->setBaudRate(QSerialPort::Baud4800);
        break;

    case 9600:
        devSerial->setBaudRate(QSerialPort::Baud9600);
        break;

    case 19200:
        devSerial->setBaudRate(QSerialPort::Baud19200);
        break;

    case 38400:
        devSerial->setBaudRate(QSerialPort::Baud38400);
        break;

    case 115200:
        devSerial->setBaudRate(QSerialPort::Baud115200);
        break;

    default:
        break;
    }

    devSerial->setDataBits(QSerialPort::Data8);
    devSerial->setParity(QSerialPort::NoParity);
    devSerial->setStopBits(QSerialPort::OneStop);
    devSerial->setFlowControl(QSerialPort::NoFlowControl);

    if(devSerial->open(QIODeviceBase::ReadWrite)){
        return true;
    }
    else{
        return false;
    }
}



bool comserial::Disconnect(){
    devSerial->clear();
    devSerial->close();

    if(devSerial->error() == 0|| !devSerial->isOpen())  {
        qDebug() << "Đã đóng cổng serial";
        return true;


    }else {
        qDebug() << "Đóng thất bại !! Error :" << devSerial->error();
                                                  return false;
    }
}

qint64 comserial::Write(const char *cmd){
    qint64 sizeWritten;
    sizeWritten = devSerial->write(cmd,qstrlen(cmd));

    return sizeWritten;
}

QString comserial::Read(){

    QString buf;
    while(devSerial->waitForReadyRead(20)){
        buf += devSerial->readAll();
    }
    return buf;
}

QString comserial::Read(int bufferSize){

    char* buf = new char[bufferSize];
    if(devSerial->canReadLine()){

        devSerial->read(buf, bufferSize);
    }
    QString str = QString::fromUtf8(buf, bufferSize);
    delete[]  buf;
    return str;
}

