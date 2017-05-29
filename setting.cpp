#include "setting.h"
#include "ui_setting.h"

setting::setting(QWidget *parent) :
   // QWidget(parent)
    ui(new Ui::setting)
{
    ui->setupUi(this);
}

setting::~setting()
{
    delete ui;
}

void setting::on_setdone_clicked()
{
    QString tmp_num = ui->roomNum->text();
    this->roomnum = tmp_num.toInt();
    QString tmp_speed = ui->defWindspeed->text();
    this->windspeed = tmp_speed.toInt();
    QString tmp = ui->defTmp->text();
    this->tmp = tmp.toDouble();
    this->IP = ui->IP->text();
    this->Port = ui->Port->text();
    emit Gotdata();
}

void setting::on_default_2_clicked()
{
    this->roomnum = 0;
    this->windspeed = 0;
    this->tmp = 27;
    this->IP = "10.201.20.244";
    this->Port = "6666";
    emit Gotdata();
}
