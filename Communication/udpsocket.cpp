#include "udpsocket.h"

UdpSocket::UdpSocket(QObject *parent): CommunicationBase()
{
    m_udpSocket = new QUdpSocket(this);
    connect(tmr,&QTimer::timeout,this,[=](){this->sendMessage("Hello Server Udp");});
}

UdpSocket::~UdpSocket()
{
    closeCommunication();
    delete m_udpSocket;
}

void UdpSocket::connectCommunication()
{
    m_udpSocket->connectToHost("172.16.40.104",7);

    if(m_udpSocket->waitForConnected(3000)){
        qDebug() << "Udp Connected";
        tmr->start(2000);
        connect(m_udpSocket,&QUdpSocket::readyRead,this,&UdpSocket::readMessage);
    }
    else{
        qCritical() << "Udp Connection error: " << m_udpSocket->errorString();
    }
}

void UdpSocket::closeCommunication()
{
    if(m_udpSocket->isOpen())
        m_udpSocket->close();
    tmr->stop();
}

void UdpSocket::sendMessage(QString message)
{
    m_udpSocket->write(message.toUtf8());
    qDebug() << "sendMessage: " << message;
    m_udpSocket->waitForBytesWritten(1000);
}

void UdpSocket::readMessage()
{
    m_udpSocket->waitForReadyRead(3000);
    qDebug() << "incomingMessage: " <<  m_udpSocket->readAll() << ", incomingMessage Size: " <<m_udpSocket->bytesAvailable();
}
