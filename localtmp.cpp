#include "localtmp.h"

LocalTmp & LocalTmp::getInstance(){
    static LocalTmp instance;
    return instance;
}

void LocalTmp::startTick(){
    this->activeTimer = new QTimer(this);
    this->activeTimer->setInterval(12*1000);
    this->activeTimer->setSingleShot(false);
    connect(activeTimer,SIGNAL(timeout()),this,SLOT(TimeOut()));
    this->activeTimer->start();
}

void LocalTmp::killTimer(){
    this->activeTimer->stop();
}

void LocalTmp::TimeOut(){
    emit TmpUp(0.1);
}
