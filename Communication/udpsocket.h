#ifndef UDPSOCKET_H
#define UDPSOCKET_H

#include "communicationbase.h"

class UdpSocket : public CommunicationBase
{
    Q_OBJECT
public:
    explicit UdpSocket(QObject *parent = nullptr);
    ~UdpSocket();

    void connectCommunication();
    void closeCommunication();

public slots:
    void sendMessage(QString message);
    void readMessage();

private:
    QUdpSocket *m_udpSocket;
    QTimer *tmr = new QTimer();

signals:
};

#endif // UDPSOCKET_H
