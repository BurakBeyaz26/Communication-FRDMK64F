#ifndef TcpSocket_H
#define TcpSocket_H

#include "communicationbase.h"

class TcpSocket : public CommunicationBase
{
    Q_OBJECT
public:
    explicit TcpSocket(QObject *parent = nullptr);
    ~TcpSocket();

    void connectCommunication();
    void closeCommunication();

public slots:
    void sendMessage(QString message);
    void readMessage();

private:
    QTcpSocket *m_tcpSocket;
    QTimer *tmr = new QTimer();

signals:
};


#endif // TcpSocket_H
