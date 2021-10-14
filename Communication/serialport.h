#ifndef SERIALPORT_H
#define SERIALPORT_H

#include "communicationbase.h"

class SerialPort : public CommunicationBase
{
    Q_OBJECT
public:
    explicit SerialPort(QObject *parent = nullptr);
    ~SerialPort();

    void connectCommunication();
    void closeCommunication();

public slots:
    void readMessage();
    void sendMessage(QString message);

private:
    QSerialPort *m_comSerial;
    QTimer *tmr = new QTimer();

signals:

};

#endif // SERIALPORT_H
