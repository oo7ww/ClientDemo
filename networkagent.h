#ifndef NETWORKAGENT_H
#define NETWORKAGENT_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QHostInfo>
#include <QHostAddress>
#include <QNetworkInterface>
#include <QList>
#include <QSettings>

#include "structures.h"

#include "json.h"

class NetworkAgent : public QObject
{
    Q_OBJECT
public:
    static NetworkAgent & getInstance();

    void ConnectToServer();
    void Send(PacketInfo packetInfo);

    QString GetCurrentDeviceIPAddress();

    void SetIPAddress(QString ip);
    void SetPortNumber(QString number);

    QString GetTargetIPAddress();
    QString GetTargetPortNumber();


signals:
    void NewMessage(PacketInfo);

private:
    explicit NetworkAgent(QObject *parent = 0);

    QTcpServer * tcpServer;
    QTcpSocket * tcpSocket;

    QString targetIPAddress;
    QString targetPortNumber;

private slots:
    void MessageReceived();

    void ConnectSuccessful();

    void GetInfoFromIni();

};

#endif // NETWORKAGENT_H
