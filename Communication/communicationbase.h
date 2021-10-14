#ifndef COMMUNICATIONBASE_H
#define COMMUNICATIONBASE_H

#include <QObject>
#include <QDebug>
#include <QTimer>
#include <QtCore>
#include <QtNetwork>

#include <QUdpSocket>
#include <QTcpSocket>
#include <QSerialPort>

class CommunicationBase : public QObject
{
    Q_OBJECT
public:

    virtual void connectCommunication() = 0;
    virtual void closeCommunication() = 0;

    virtual ~CommunicationBase(){}

public slots:
    virtual void sendMessage(QString message) = 0;
    virtual void readMessage() = 0;

private:

signals:

};





#endif // COMMUNICATIONBASE_H
