#ifndef CLIENTDEMO_H
#define CLIENTDEMO_H

#include <QMainWindow>
#include "networkagent.h"
#include "localtmp.h"
#include "setting.h"

namespace Ui {
class ClientDemo;
}

class ClientDemo : public QMainWindow
{
    Q_OBJECT

public:
    PacketInfo Encap();
    explicit ClientDemo(QWidget *parent = 0);
    void initilize();
    ~ClientDemo();
signals:
    void ServerOff(bool flag);
    void ServerOn(bool flag);
private slots:
    void on_PowerOn_clicked();

    //void on_TmpAdjust_valueChanged(int arg1);

    void on_SpeedAdjust_currentIndexChanged(int index);

    void on_PowerDown_clicked();

    void readMessage(PacketInfo Packet);

    void on_Connect_clicked();
    void pending();

    void on_actionsettings_triggered();
    void on_settingsdone();

    void on_up_clicked();

    void on_down_clicked();

private:
    Ui::ClientDemo *ui;
    NetworkAgent* agent;
    LocalTmp* localtmp;
    //PacketInfo argument;
    QString roomIP;
    QString roomPort;
    int roomNum; //房间号
    int windSpeed;//风速
    double roomTmp;//室温
    double targetTmp;//目标温度
    int mode;//工作模式
    bool power;//开关机
    bool isServed;//是否被服务
    double defRoomTmp;//
    double defTargetTmp;
    int defWindspeed;
    double Kwh;
    double fee;
    double lowestTmp;
    double highestTmp;
    setting* child;
    int flag = 0;
    int connected;
    int poweron;
};

#endif // CLIENTDEMO_H
