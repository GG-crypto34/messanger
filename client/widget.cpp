#include "widget.h"
#include "factory/checkname.h"
#include "factory/sendmessage.h"
#include "ui_widget.h"
#include "message.h"
#include "login.h"
#include <QStringList>
#include <qjsondocument.h>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    connect(ui->pushButton, &QPushButton::clicked, this, &Widget::sendMessage);
    l=new Login;
    connect(l, &Login::pushButton,[this](QString ip, QString login){
        Widget::login=login;
        socket.connectToHost(ip,6000);
        if(socket.waitForConnected(30000)){
            auto json = CheckName(login).build();
            QJsonDocument doc(json);
            socket.write(doc.toJson(QJsonDocument::Compact));
            qDebug() << "connected to server: " << doc;
        }
        else{
            qDebug() << "failed to connect to server";
        }
    });
    QWidget::connect(&socket, &QTcpSocket::readyRead, this, &Widget::newMessage);
    commands["accept_name"]=[this](const QJsonObject& json){accept_name(json);};
    commands["update_list"]=[this](const QJsonObject& json){update_list(json);};
    l->exec();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::newMessage()
{
    QJsonDocument jsonDoc = QJsonDocument::fromJson(socket.readAll());
    qDebug() << "incoming json: " << jsonDoc;
    if (!jsonDoc.isObject()) {
        qDebug() << "Invalid JSON!";
        return;
    }
    // Извлекаем JSON объект
    QJsonObject jsonObject = jsonDoc.object();
    commands[jsonObject["type"].toString()](jsonObject);
}

void Widget::accept_name(const QJsonObject &json)
{
    if(json["accept"].toString()=="succed"){
        l->close();
    }
    else{
        //ошибка в имени
    }
}

void Widget::sendMessage(){
    QString message = ui->lineEdit->text();
    if(message.isEmpty()) return;
    QJsonObject json=SendMessage(message).from(login).toAll().build();
    ui->lineEdit->clear();
    ui->scrollAreaWidgetContents->layout()->addWidget(new Message(login, message));
    QJsonDocument doc(json);
    socket.write(doc.toJson(QJsonDocument::Compact));
    qDebug() << "sent message: " << doc;

}

void Widget::update_list(const QJsonObject& jsn){
    QJsonArray arr=jsn["users"].toArray();
    QStringList users;
    for(auto user : arr){
        QJsonObject obj=user.toObject();
        QString name=obj["name"].toString();
        if(name!=login){
            users.append(name);
        }
    }
    ui->userslist->clear();
    ui->userslist->addItem("All");
    ui->userslist->addItems(users);
}
