#include "message.h"
#include "ui_message.h"

Message::Message(QString name, QString text)
:ui(new Ui::Message)
{
    ui->setupUi(this);
    ui->name->setText(name);
    ui->text->setText(text);
    ui->verticalLayout->setAlignment(Qt::AlignTop);
}

Message::~Message()
{
    delete ui;
}
