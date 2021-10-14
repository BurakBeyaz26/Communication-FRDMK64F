#include "tcpsocket.h"

TcpSocket::TcpSocket(QObject *parent)
{    
    m_tcpSocket = new QTcpSocket(this);
    connect(tmr,&QTimer::timeout,this,[=](){this->sendMessage("Hello Server Tcp");});
}

TcpSocket::~TcpSocket()
{
    closeCommunication();
    delete m_tcpSocket;
}

void TcpSocket::connectCommunication(){

    m_tcpSocket->connectToHost("172.16.40.103",7);

    if(m_tcpSocket->waitForConnected(3000)){
        qDebug() << "Tcp Connected";
        tmr->start(2000);
        connect(m_tcpSocket,&QTcpSocket::readyRead,this,&TcpSocket::readMessage);
    }
    else{
        qCritical() << "Tcp Connection error: " << m_tcpSocket->errorString();
    }
}

void TcpSocket::closeCommunication()
{
    if(m_tcpSocket->isOpen())
        m_tcpSocket->close();
    tmr->stop();
}

void TcpSocket::sendMessage(QString message)
{
    m_tcpSocket->write(message.toUtf8());
    qDebug() << "sendMessage: " << message;
    m_tcpSocket->waitForBytesWritten(1000);
}

void TcpSocket::readMessage()
{
    m_tcpSocket->waitForReadyRead(3000);
    qDebug() << "incomingMessage: " <<  m_tcpSocket->readAll() << ", incomingMessage Size: " <<m_tcpSocket->bytesAvailable();
}
