#include "clientdemo.h"
#include "ui_clientdemo.h"
#include "setting.h"
#include <QDebug>

ClientDemo::ClientDemo(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ClientDemo)
{
    ui->setupUi(this);
    ui->WindSpeed->setEnabled(false);
    ui->Fee->setEnabled(false);
    ui->Mode->setEnabled(false);
    ui->Fee->setEnabled(false);
    ui->RoomTmp->setEnabled(false);
    ui->TargetTmp->setEnabled(false);
    ui->RoomNo->setEnabled(false);

    //network agent
    agent = &(NetworkAgent::getInstance());
    //local temperature adjust
    localtmp = &(LocalTmp::getInstance());

    connect(this,SIGNAL(ServerOn(bool)),localtmp,SLOT(killTimer()));
    connect(localtmp,SIGNAL(TmpUp(double)),this,SLOT(pending()));
    connect(this,SIGNAL(ServerOff(bool)),localtmp,SLOT(startTick()));
    connect(agent,SIGNAL(NewMessage(PacketInfo)),this,SLOT(readMessage(PacketInfo)));
}

ClientDemo::~ClientDemo()
{
    delete ui;
}

PacketInfo ClientDemo::Encap()
{
    PacketInfo packet;
    packet.defRoomTmp = this->defRoomTmp;
    packet.highestTmp = this->highestTmp;
    packet.lowestTmp = this->lowestTmp;
    packet.power = this->power;
    packet.roomNum = this->roomNum;
    packet.roomTmp = this->roomTmp;
    packet.windSpeed = this->windSpeed;
    packet.targetTmp = this->targetTmp;
    packet.isServed = false;
    return packet;
}

void ClientDemo::initilize()
{
    this->roomTmp = this->defRoomTmp;
    this->targetTmp = this->defRoomTmp;
    this->power = 1;
}

void ClientDemo::on_Connect_clicked()
{
/*  argument.roomNum = this->roomNum;
    argument.power = 0;
    argument.targetTmp = 25;
    argument.roomTmp = this->deftmp;
    argument.lowestTmp = 18;
    argument.highestTmp = 25;
    argument.windSpeed = 0;
*/
    this->power = 0;
    this->targetTmp = this->defRoomTmp;
    this->roomTmp = this->defRoomTmp;

    connected = 1;
    flag = 0;
    agent->SetIPAddress(this->roomIP);
    agent->SetPortNumber(this->roomPort);
    agent->ConnectToServer();

    agent->Send(Encap());
    qDebug()<<"connecting";
    qDebug()<<"room num"<<this->roomNum;
    qDebug()<<"room IP"<<this->roomIP;
    //qDebug()<<"roomNum local"<<argument.roomNum;
}

void ClientDemo::on_PowerOn_clicked()
{
    qDebug()<<"power on clicked";
    //ui->WindSpeed->setText("1");
    //ui->SpeedAdjust->setCurrentIndex(1);
    ui->Fee->setText("0");
    ui->RoomTmp->setText(QString::number(this->defRoomTmp));
    QString temp = QString::number(this->roomNum);
    ui->RoomNo->setText(temp);
/*
    argument.roomTmp = this->deftmp;
    argument.defRoomTmp = this->deftmp;
    argument.fee = 0;
    argument.Kwh = 0;
    argument.windSpeed = this->defWindspeed;
    argument.power = 1;
    argument.targetTmp = 25;
    argument.lowestTmp = 18;
    argument.highestTmp = 25;
    argument.roomNum = this->roomNum;
*/
     //this->targetTmp = this->defRoomTmp;
    //this->roomTmp = this->defRoomTmp;

    connected = 1;
    flag = 0;
    agent->SetIPAddress(this->roomIP);
    agent->SetPortNumber(this->roomPort);
    agent->ConnectToServer();
    initilize();
    poweron = 1;
    agent->Send(Encap());

}

void ClientDemo::on_SpeedAdjust_currentIndexChanged(int index)
{
    ui->WindSpeed->setText(QString::number(index));
    if(this->windSpeed != index){
        this->windSpeed =  index;
        qDebug()<<"speed adjusted";
        agent->Send(Encap());
    }
}

void ClientDemo::on_PowerDown_clicked()
{
    qDebug()<<"power Down";
    //argument.roomNum = this->roomNum;
    //argument.power = 0;
    this->power = 0;
    poweron = 0;
    agent->Send(Encap());
    //flag = 0;
}

void ClientDemo::readMessage(PacketInfo packet)
{
    if(connected == 1){
        this->highestTmp = packet.highestTmp;
        this->lowestTmp = packet.lowestTmp;
        this->mode = packet.mode;
        this->targetTmp = packet.targetTmp;
        //this->isServed = packet.isServed;
        ui->TmpAdjust->setText(QString::number(packet.targetTmp));
        ui->TargetTmp->setText(QString::number(packet.targetTmp));
        connected = 0;
        //qDebug()<<"first packet received:"<<packet.targetTmp;
    }
    else{
        ui->RoomTmp->setText((QString::number(packet.roomTmp)));
        ui->Fee->setText((QString::number(packet.fee)));
    }
    this->roomTmp = packet.roomTmp;

    if(packet.mode){
        ui->Mode->setText("heat");
        this->mode = packet.mode;
    }
    else{
        ui->Mode->setText("cool");
        this->mode = packet.mode;
    }

    if(!packet.isServed){
        emit ServerOff(packet.isServed);
    }
    else{
        emit ServerOn(packet.isServed);
    }
}

void ClientDemo::pending(){
    qDebug()<<"pending";
    if(abs(this->roomTmp-this->defRoomTmp) <= 0.05){
        ;
    }
    else if(this->roomTmp > this->defRoomTmp && this->roomTmp < this->highestTmp)
    {
        this->roomTmp -= 0.1;
    }
    else if(this->roomTmp > this->defRoomTmp && this->roomTmp > this->lowestTmp)
    {
        this->roomTmp -= 0.1;
    }
    else if(this->roomTmp < this->defRoomTmp && this->roomTmp < this->highestTmp)
    {
        this->roomTmp += 0.1;
    }
    else{
        this->roomTmp += 0.1;
    }    

    agent->Send(Encap());
}

void ClientDemo::on_actionsettings_triggered()
{
     this->child = new setting();
     connect(child,SIGNAL(Gotdata()),this,SLOT(on_settingsdone()));
     this->child->show();
}

void ClientDemo::on_settingsdone()
{
    this->roomNum = this->child->roomnum;
    this->roomIP = this->child->IP;
    this->roomPort = this->child->Port;
    this->defRoomTmp = this->child->tmp;
    qDebug()<<this->defRoomTmp;
    this->defWindspeed = this->child->windspeed;
    this->child->close();
}

void ClientDemo::on_up_clicked()
{
    if(this->targetTmp < this->highestTmp && this->targetTmp > this->lowestTmp){
        this->targetTmp = this->targetTmp + 1;
        ui->TmpAdjust->setText(QString::number(this->targetTmp));
        qDebug()<<"up send";
        //qDebug()<<Encap();

        agent->Send(Encap());
    }

}

void ClientDemo::on_down_clicked()
{
    /*if(this->targetTmp > this->lowestTmp && this->targetTmp < this->highestTmp){
        this->targetTmp = this->targetTmp - 1;
        qDebug()<<"down send";
        //qDebug() << Encap();
        agent->Send(Encap());
    }*/
    this->targetTmp = this->targetTmp - 1;
    ui->TmpAdjust->setText(QString::number(this->targetTmp));
    qDebug()<<"down send";
    //qDebug() << Encap();
    agent->Send(Encap());
}
