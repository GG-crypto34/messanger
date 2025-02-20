#ifndef USER_H
#define USER_H

#include <QObject>
#include <QTcpSocket>

class User : public QTcpSocket
{
    Q_OBJECT
public:
    QString name, status;
};

#endif // USER_H
