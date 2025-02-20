#include "login.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QVBoxLayout>
#include <qlineedit.h>
#include <qpushbutton.h>

Login::Login() {
    QHBoxLayout* hLayout=new QHBoxLayout;
    setLayout(hLayout);
    auto vLayout = new QVBoxLayout;
    hLayout->addLayout(vLayout);
    auto v2Layout = new QVBoxLayout;
    hLayout->addLayout(v2Layout);
    QLabel* ip= new QLabel("Введите Ip адресс");
    QLabel* login= new QLabel("Введите логин");
    QLineEdit* ipInp = new QLineEdit("127.0.0.1");
    QLineEdit* loginInp = new QLineEdit("login");
    vLayout->addWidget(ip);
    vLayout->addWidget(ipInp);
    vLayout->addWidget(login);
    vLayout->addWidget(loginInp);
    QPushButton* ok = new QPushButton("ok");
    v2Layout->addSpacerItem(new QSpacerItem(0,0,QSizePolicy::Minimum,QSizePolicy::Expanding));
    v2Layout->addWidget(ok);
    connect(ok,&QPushButton::pressed,[this, ipInp, loginInp](){
        emit pushButton(ipInp->text(), loginInp->text());
    });

// добавить обозначение ошибки ввода ip или логина
}

