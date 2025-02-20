#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <QObject>

class Login : public QDialog
{
    Q_OBJECT
public:
    Login();
signals:
    void pushButton(QString ip, QString login);
};


#endif // LOGIN_H
