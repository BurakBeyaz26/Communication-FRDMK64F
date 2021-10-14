#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>
#include <QQmlContext>

#include "serialport.h"
#include "tcpsocket.h"
#include "udpsocket.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QQuickStyle::setStyle("Material");
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

#if 1
    CommunicationBase *serr = new SerialPort();
    serr->connectCommunication();
#endif

#if 1
    CommunicationBase *sock_tcp = new TcpSocket();
    sock_tcp->connectCommunication();
#endif

#if 1
    CommunicationBase *sock_udp = new UdpSocket();
    sock_udp->connectCommunication();
#endif

    return app.exec();
}
