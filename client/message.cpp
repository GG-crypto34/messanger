#include "message.h"
#include "ui_message.h"
#include <QDate>
#include <QDateTime>
#include <QTime>

Message::Message(QString name, QString text, QString date)
    :ui(new Ui::Message)
{
    ui->setupUi(this);
    ui->name->setText(name);
    ui->text->setText(text);
    ui->date->setText(date);
}

Message::~Message()
{
    delete ui;
}
