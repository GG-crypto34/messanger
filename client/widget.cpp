#include "widget.h"
#include "factory/checkname.h"
#include "ui_widget.h"
#include "message.h"
#include "login.h"

#include <qjsondocument.h>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->scrollAreaWidgetContents->layout()->addWidget(new Message);
    ui->scrollAreaWidgetContents->layout()->addWidget(new Message);
    ui->scrollAreaWidgetContents->layout()->addWidget(new Message);
    Login l;
    l.exec();
    connect(&l, &Login::pushButton,[this](QString ip, QString login){
        Widget::login=login;
        socket.connectToHost(ip,6000);
        if(socket.waitForConnected(30000)){
            auto json = CheckName(login).build();
            QJsonDocument doc(json);
            socket.write(doc.toJson(QJsonDocument::Compact));
        }
    });
    QWidget::connect(&socket, &QTcpSocket::readyRead, this, &Widget::newMessage);
    commands["accept_name"]=[this](const QJsonObject& json){accept_name(json);};
}

Widget::~Widget()
{
    delete ui;
}

void Widget::newMessage()
{
    QJsonDocument jsonDoc = QJsonDocument::fromJson(socket.readAll());
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

    }
    else{
        //ошибка в имени
    }
}
