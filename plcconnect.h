#ifndef PLCCONNECT_H
#define PLCCONNECT_H

#include <QObject>
#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include <QtSerialPort/QSerialPort>
#include "global.h"



class PLCConnect : public QObject
{
    Q_OBJECT
public:
    PLCConnect(QObject *parent = 0);
    ~PLCConnect();
    void sendDataToPLC(int result);//package data

signals:
    void parsePLCDataOver(PLCData *data);

private slots:
    void handDataFromPLC();//receive data
    void onparsePLCDataOver(PLCData *data);//parse data
private:
    void PackgePLCData();
    void ParsePLCData();
    void SerialPortInit(QSerialPort *Serial);
    QObject *myparent;



};
#endif // PLCCONNECT_H
