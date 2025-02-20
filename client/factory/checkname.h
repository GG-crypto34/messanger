#pragma once
#include <QObject>
#include <QJsonArray>
#include <QJsonObject>

class CheckName
{
private:
    QString name;
public:
    CheckName(QString name):name(name){}
    QJsonObject build();
};

QJsonObject CheckName::build()
{
    if(name.isEmpty()) throw std::invalid_argument("name is empty");
    QJsonObject json;
    json["type"]="check_name";
    json["name"]=name;
    return json;
}
