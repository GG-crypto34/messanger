#ifndef SERVER_H
#define SERVER_H
#include "user.h"
#include <QMap>
#include <QObject>
#include <QTcpServer>
class Server : public QTcpServer
{
    Q_OBJECT
public:
    Server();

private:
    QMap<QString, std::function<void(const QJsonObject&, User*)>> commands;
    void check_name(const QJsonObject& , User*);
    void change_status(const QJsonObject&, User*);
    void send_message(const QJsonObject&, User*);
    void public_message(const QJsonObject&, User*);
    void private_message(const QJsonObject&, User*);
    void update_list();
    QSet<User*> users;
    void incomingConnection(qintptr socketDescriptor) override;
    bool isValid(const QString& name);
private slots:
    void newMessage();
    void disconnect();
};

#endif // SERVER_H
