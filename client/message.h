#ifndef MESSAGE_H
#define MESSAGE_H

#include <QWidget>

namespace Ui {
class Message;
}

class Message : public QWidget
{
    Q_OBJECT

public:
    Message(QString name, QString text);
    ~Message();

private:
    Ui::Message *ui;
};

#endif // MESSAGE_H
