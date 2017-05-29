#include "networkagent.h"

NetworkAgent::NetworkAgent(QObject *parent) : QObject(parent)
{
    tcpServer=new QTcpServer();

    tcpSocket=NULL;

    QSettings settings("config.txt", QSettings::IniFormat);
    settings.beginGroup("Config");
    settings.setValue("IPAddress", "127.0.0.1");
    settings.setValue("PortNumber", "9800");
    settings.endGroup();

    GetInfoFromIni();

    qDebug()<<targetIPAddress;
    qDebug()<<targetPortNumber;
}

NetworkAgent & NetworkAgent::getInstance(){
    static NetworkAgent instance;
    return instance;
}

void NetworkAgent::ConnectToServer(){
    qDebug()<<"try to connect";
    tcpSocket=new QTcpSocket();
    tcpSocket->abort();

    tcpSocket->connectToHost(QHostAddress(targetIPAddress), targetPortNumber.toInt());
    connect(tcpSocket, SIGNAL(connected()), this, SLOT(ConnectSuccessful()));
    connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(MessageReceived()));
}

void NetworkAgent::Send(PacketInfo packetInfo){
    if(tcpSocket==NULL) return;
    QString str=Json::Serialize(packetInfo);


    tcpSocket->write(str.toStdString().c_str(), strlen(str.toStdString().c_str()));
    tcpSocket->waitForBytesWritten();
    qDebug()<<str;
}

void NetworkAgent::MessageReceived(){
    qDebug()<<"receive a message";
    QByteArray packet=tcpSocket->readAll();
    QString json=QString(packet);

    qDebug()<<json;

    PacketInfo packetInfo=Json::DeSerialize(json);
    qDebug()<<"defRoomTmp: "<<packetInfo.defRoomTmp;
    qDebug()<<"fee: "<<packetInfo.fee;
    qDebug()<<"isServed: "<<packetInfo.isServed;
    qDebug()<<"Kwh: "<<packetInfo.Kwh;
    qDebug()<<"mode: "<<packetInfo.mode;
    qDebug()<<"power: "<<packetInfo.power;
    qDebug()<<"roomNum: "<<packetInfo.roomNum;
    qDebug()<<"roomTmp: "<<packetInfo.roomTmp;
    qDebug()<<"targetTmp: "<<packetInfo.targetTmp;
    qDebug()<<"windSpeed: "<<packetInfo.windSpeed;

    emit NewMessage(packetInfo);

}

void NetworkAgent::ConnectSuccessful(){
    qDebug()<<"connect successful";
}

QString NetworkAgent::GetCurrentDeviceIPAddress(){
    QString ipAddr;
    QString localHost = QHostInfo::localHostName();
    #if 0
        QList<QHostAddress> AddressList = QNetworkInterface::allAddresses();
        foreach(QHostAddress address, AddressList){
            if(address.protocol() == QAbstractSocket::IPv4Protocol &&
                    address != QHostAddress::Null &&
                    address != QHostAddress::LocalHost){
                if (address.toString().contains("127.0.")){
                    continue;
                }
                ipAddr = address.toString();
                break;
            }
        }
    #else
        QHostInfo info = QHostInfo::fromName(localHost);
        info.addresses();//QHostInfo的address函数获取本机ip地址
        //如果存在多条ip地址ipv4和ipv6：
        foreach(QHostAddress address,info.addresses())
        {
            if(address.protocol()==QAbstractSocket::IPv4Protocol){//只取ipv4协议的地址
                qDebug()<<address.toString();
                ipAddr = address.toString();
            }
        }
    #endif
        return ipAddr;
}

void NetworkAgent::SetIPAddress(QString ip){
    targetIPAddress=ip;
}

void NetworkAgent::SetPortNumber(QString number){
    targetPortNumber=number;
}

QString NetworkAgent::GetTargetIPAddress(){
    return targetIPAddress;
}

QString NetworkAgent::GetTargetPortNumber(){
    return targetPortNumber;
}

void NetworkAgent::GetInfoFromIni(){
    QSettings settings("config.txt", QSettings::IniFormat);
    targetIPAddress=settings.value("Config/IPAddress").toString();
    targetPortNumber=settings.value("Config/PortNumber").toString();
}




















