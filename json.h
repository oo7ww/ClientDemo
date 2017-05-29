#ifndef JSON_H
#define JSON_H

#include <QObject>
#include <QJsonParseError>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QDebug>

#include "structures.h"

class Json : public QObject
{
    Q_OBJECT
public:
    explicit Json(QObject *parent = 0);

    static QString Serialize(PacketInfo packetInfo);
    static PacketInfo DeSerialize(QString json);


signals:

public slots:
};

#endif // JSON_H

