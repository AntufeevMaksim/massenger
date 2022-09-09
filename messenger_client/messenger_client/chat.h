#ifndef CHAT_H
#define CHAT_H

#include <QMainWindow>
#include "serverinterface.h"
#include "ui_chat.h"
#include <QTimer>
#include "usertype.h"

namespace Ui {
class Chat;
}

class Chat : public QMainWindow
{
    Q_OBJECT

public:
    explicit Chat(QWidget *parent, int user_id, int friend_id, QString& friend_name, ServerInterface *_server);
    Chat();

private slots:
    void on_send_message_button_clicked();
    void CheckNewMessage();

private:
    void AddNewMessage(QString& text, UserType user_type);
    int _user_id;
    int _friend_id;
    QString _friend_name;
    ServerInterface *server;
    QTimer check_new_message;
    std::unique_ptr<Ui::Chat> ui = std::make_unique<Ui::Chat>();

};

#endif // CHAT_H
