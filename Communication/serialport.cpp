#include "serialport.h"

SerialPort::SerialPort(QObject *parent)
{
    m_comSerial = new QSerialPort(this);
    connect(tmr,&QTimer::timeout,this,[=](){this->sendMessage("Hello Server Serial");});
}

SerialPort::~SerialPort()
{
    closeCommunication();
    delete m_comSerial;
}

void SerialPort::connectCommunication()
{
    m_comSerial->setPortName("COM3");
    m_comSerial->setBaudRate(QSerialPort::Baud115200);
    m_comSerial->setDataBits(QSerialPort::Data8);
    m_comSerial->setParity(QSerialPort::NoParity);
    m_comSerial->setStopBits(QSerialPort::OneStop);
    m_comSerial->setFlowControl(QSerialPort::NoFlowControl);

    if (m_comSerial->open(QIODevice::ReadWrite))
    {
        qDebug() << "Serial Connected";
        connect(m_comSerial, &QSerialPort::readyRead, this,&SerialPort::readMessage);
        tmr->start(2000);
    }
    else
    {
        qCritical() << "Serial Connection Error: " << m_comSerial->errorString();
    }
}

void SerialPort::closeCommunication()
{
     if(m_comSerial->isOpen())
         m_comSerial->close();
     tmr->stop();
}

void SerialPort::sendMessage(QString message)
{
    m_comSerial->write(message.toUtf8());
    qDebug() << "sendMessage: " << message;
    m_comSerial->waitForBytesWritten(1000);
}

void SerialPort::readMessage()
{
    m_comSerial->waitForBytesWritten(3000);
    qDebug() << "incomingMessage: " <<  m_comSerial->readAll() << ", incomingMessage Size: " <<m_comSerial->bytesAvailable();
}
