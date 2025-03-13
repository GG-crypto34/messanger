#pragma once
#include <QJsonObject>

class SendMessage
{
private:
    QString message;
    QString receiver;
    QString sender;
    bool all= false;
public:
    SendMessage(QString message):message(message){}
    SendMessage& toAll(){
        all = true;
        return *this;
    }
    SendMessage& toReceiver(QString name){
        receiver = name;
        return *this;
    }
    SendMessage& from(QString name){
        sender = name;
        return *this;
    }
    QJsonObject build();
};

QJsonObject SendMessage::build()
{
    if(message.isEmpty()) throw std::invalid_argument("message is empty");
    if(sender.isEmpty()) throw std::invalid_argument("empty sender name");
    if(!all && receiver.isEmpty()) throw std::invalid_argument("please call 'toAll' or 'toReceiver' ");
    if(all && !receiver.isEmpty()) throw std::invalid_argument("cant send to all and to user at the same time");

    QJsonObject json;
    json["type"] = "send_message";
    json["message"] = message;
    json["receiver"] = all ? "all" : receiver;
    json["sender"] = sender;
    return json;
}
