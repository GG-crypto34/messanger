#ifndef ACCEPTNAME_H
#define ACCEPTNAME_H
#include <QObject>
#include <QJsonArray>
#include <QJsonObject>

class AcceptName
{
private:
    QString accept;
public:
    AcceptName& setAccept(const QString& accept);
    QJsonObject build();
};

AcceptName& AcceptName::setAccept(const QString& accept)
{
    this->accept=accept;
    return *this;
}

QJsonObject AcceptName::build()
{
    QJsonObject json;
    json["type"]="accept_name";
    json["accept"]=accept;
    return json;
}

#endif // ACCEPTNAME_H
