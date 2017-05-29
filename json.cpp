#include "json.h"

Json::Json(QObject *parent) : QObject(parent)
{

}

QString Json::Serialize(PacketInfo packetInfo){
    QString result;

    QJsonObject json;

    json.insert("roomNum", packetInfo.roomNum);
    json.insert("roomTmp", packetInfo.roomTmp);
    json.insert("targetTmp", packetInfo.targetTmp);
    json.insert("windSpeed", packetInfo.windSpeed);
    json.insert("power", packetInfo.power);
    json.insert("isServed", packetInfo.isServed);
    json.insert("mode", packetInfo.mode);
    json.insert("defRoomTmp", packetInfo.defRoomTmp);
    json.insert("Kwh", packetInfo.Kwh);
    json.insert("fee", packetInfo.fee);
    json.insert("lowestTmp", packetInfo.lowestTmp);
    json.insert("highestTmp", packetInfo.highestTmp);
    QJsonDocument document;
    document.setObject(json);
    QByteArray byte_array=document.toJson(QJsonDocument::Compact);
    result=QString(byte_array);

    return result;
}


PacketInfo Json::DeSerialize(QString json){
    PacketInfo result;
    qDebug()<<json;
    QByteArray byte_array;
    QJsonParseError json_error;
    QJsonDocument parse_doucment = QJsonDocument::fromJson(byte_array.append(json), &json_error);
    if(json_error.error==QJsonParseError::NoError){
        if(parse_doucment.isObject()){
            QJsonObject obj=parse_doucment.object();
            if(obj.contains("roomNum")){
                result.roomNum=obj.take("roomNum").toInt();
            }
            if(obj.contains("roomTmp")){
                result.roomTmp=obj.take("roomTmp").toDouble();
            }
            if(obj.contains("targetTmp")){
                result.targetTmp=obj.take("targetTmp").toDouble();
            }
            if(obj.contains("windSpeed")){
                result.windSpeed=obj.take("windSpeed").toInt();
            }
            if(obj.contains("power")){
                result.power=obj.take("power").toBool();
            }
            if(obj.contains("isServed")){
                result.isServed=obj.take("isServed").toBool();
            }
            if(obj.contains("mode")){
                result.mode=obj.take("mode").toInt();
            }
            if(obj.contains("defRoomTmp")){
                result.defRoomTmp=obj.take("defRoomTmp").toDouble();
            }
            if(obj.contains("Kwh")){
                result.Kwh=obj.take("Kwh").toDouble();
            }
            if(obj.contains("fee")){
                result.fee=obj.take("fee").toDouble();
            }
            if(obj.contains("highestTmp")){
                result.highestTmp = obj.take("highestTmp").toDouble();
            }
            if(obj.contains("lowestTmp")){
                result.lowestTmp = obj.take("lowestTmp").toDouble();
            }
        }
        else{
            qDebug()<<"is not object";
        }
    }
    else{
        qDebug()<<"json error";
    }
    return result;
}

