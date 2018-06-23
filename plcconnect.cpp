#include "plcconnect.h"

static QSerialPort *serialPLC;
static QWaitCondition serialPLCNotUse;
static QMutex mutex;
static PLCData *GneedPackgePLCData = NULL;
static PLCData *GneedParsePLCData = NULL;
PLCConnect::PLCConnect(QObject *parent) :
    QObject(parent),
    myparent(parent)
{
    GneedPackgePLCData = new PLCData;
    GneedParsePLCData = new PLCData;
    serialPLC = new  QSerialPort(this);
    SerialPortInit(serialPLC);
    connect(serialPLC, SIGNAL(readyRead()), this, SLOT(handDataFromPLC()));
     connect(this,SIGNAL(parsePLCDataOver(PLCData*)),this,SLOT(onparsePLCDataOver(PLCData*)));
}

PLCConnect::~PLCConnect()
{
    delete GneedPackgePLCData;
    GneedPackgePLCData =NULL;
    delete GneedParsePLCData;
    GneedParsePLCData =NULL;

}

void PLCConnect::sendDataToPLC(int result)
{
    //insert result to the frame
    QByteArray requestData;
    requestData.resize(6);
    requestData[0] = 0x3c;
    requestData[1] = 0xb8;
    requestData[2] = 0x64;
    requestData[3] = 0x18;
    requestData[4] = 0xca;
    requestData[5] = GneedPackgePLCData->cmd;

    //send data
    if (!serialPLC->isWritable())
    {
        return;
    }
    serialPLC->write(requestData);
}

void PLCConnect::handDataFromPLC()
{
    if (!serialPLC->isReadable())
       {
           return;
       }
       QByteArray receiveData = serialPLC->readAll();
       //parse this data
       int size = receiveData.size();
       GneedParsePLCData->cmd = (char)receiveData.at(0);
       for(int i = 0; i < size; i++)
       {
           printf("%x",receiveData.at(i));
           if(i >= size - 1)
           {
               printf("\n");
           }
       }
       emit parsePLCDataOver(GneedParsePLCData);
}

void PLCConnect::onparsePLCDataOver(PLCData *data)
{
    //take data
    qDebug()<<"cmd ="<<data->cmd<<endl;
}

void PLCConnect::SerialPortInit(QSerialPort *serial)
{
    serial->setPortName("/dev/ttyUSB1");
    serial->setBaudRate(QSerialPort::Baud115200);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);
    if (serial->open(QIODevice::ReadWrite)) {
        qDebug()<< "serial->open success\n";
    } else {
        qDebug()<< "serial->open failed\n";
    }
}



