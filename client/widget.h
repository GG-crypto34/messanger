#ifndef WIDGET_H
#define WIDGET_H
#include <QTcpSocket>
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Login;

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
private slots:
    void newMessage();
    void sendMessage();

private:
    Ui::Widget *ui;
    QTcpSocket socket;
    QString login;
    QMap<QString, std::function<void(const QJsonObject&)>> commands;
    void accept_name(const QJsonObject&);
    void update_list(const QJsonObject&);
    Login* l;
};
#endif // WIDGET_H
