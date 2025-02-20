#ifndef ACCEPTNAME_H
#define ACCEPTNAME_H
#include <QObject>
#include "../user.h"
#include <QJsonArray>
#include <QJsonObject>

class AcceptName
{
private:
    QString accept;
    QSet<User*> users;
public:
    AcceptName& setAccept(const QString& accept);
    AcceptName& setUsers(const QSet<User*>& users);
    QJsonObject build();
};

AcceptName& AcceptName::setAccept(const QString& accept)
{
    this->accept=accept;
}

AcceptName& AcceptName::setUsers(const QSet<User*>& users)
{
    this->users=users;
}

QJsonObject AcceptName::build()
{
    QJsonObject json;
    json["type"]="accept_name";
    json["accept"]=accept;
    if(accept=="succed"){
        QJsonArray arr;
        for(auto user:users){
            QJsonObject j;
            j["name"]=user->name;
            j["status"]=user->status;
            arr.append(j);
        }
        json["users"]=arr;
    }
    return json;
}

#endif // ACCEPTNAME_H
