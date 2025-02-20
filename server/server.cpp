#include "server.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QTcpSocket>
#include <QMessageBox>
#include "factory/acceptname.h"

Server::Server()
{
    if(!listen(QHostAddress::Any,6000)){
        QMessageBox::critical(nullptr, "Listener Error", "failed listening on port 6000");
        return;
    }
    commands["public_message"]=[this](const QJsonObject& json, User* user){public_message(json, user);};
    commands["private_message"]=[this](const QJsonObject& json, User* user){private_message(json, user);};
    commands["change_status"]=[this](const QJsonObject& json, User* user){change_status(json, user);};
    commands["check_name"]=[this](const QJsonObject& json, User* user){check_name(json, user);};
}

void Server::check_name(const QJsonObject& json, User* user)
{
    QString name= json["name"].toString();
    if(!isValid(name)){
        auto jsonObj = AcceptName().setAccept("invalid").build();
        QJsonDocument doc(jsonObj);
        user->write(doc.toJson());
    }
    user->name=name;
    user->status="active";
    auto jsonObj = AcceptName().setAccept("succed").setUsers(users).build();
    QJsonDocument doc(jsonObj);
    user->write(doc.toJson());
}

void Server::public_message(const QJsonObject&, User*)
{

}

void Server::private_message(const QJsonObject&, User*)
{

}

void Server::change_status(const QJsonObject&, User*)
{

}

void Server::incomingConnection(qintptr socketDescriptor)
{
    User* user= new User;
    if(!user->setSocketDescriptor(socketDescriptor)){
        delete user;
        return;
    }
    QObject::connect(user, &QTcpSocket::readyRead, this, &Server::newMessage);
    QObject::connect(user, &QTcpSocket::disconnected, this, &Server::disconnect);
    users.insert(user);
}

bool Server::isValid(const QString &name)
{
    for(auto user:users){
        if(name==user->name) return false;
    }
    return true;
}

void Server::newMessage()
{
    auto user=dynamic_cast<User*>(sender());

    QJsonDocument jsonDoc = QJsonDocument::fromJson(user->readAll());

    if (!jsonDoc.isObject()) {
        qDebug() << "Invalid JSON!";
        return;
    }

    // Извлекаем JSON объект
    QJsonObject jsonObject = jsonDoc.object();
    commands[jsonObject["type"].toString()](jsonObject, user); //вызываем нужную функцию и передаем параметр
}

void Server::disconnect()
{

}
