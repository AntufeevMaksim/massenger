#include "chat.h"

#include <QListWidget>
#include <QListWidgetItem>
#include "serverinterface.h"
#include <thread>
#include <chrono>
#include <iostream>

void Chat::CheckNewMessage(){
    QString message = server->ReadMessage(friend_name, Message::REGULAR);
    if (!message.isEmpty()){
        AddNewMessage(message, friend_user);
    }
}


void Chat::AddNewMessage(QString& text, userType user_type){
    QListWidgetItem *new_message = new QListWidgetItem;
    new_message->setText(text);
    if (user_type == this_user){
        new_message->setBackground(Qt::green);
    }
    ui->user_chat->addItem(new_message);


}





Chat::Chat(QWidget *parent, QString& _user_name, QString& _friend_name, ServerInterface *_server) :
    QMainWindow(parent)
{
    ui->setupUi(this);
    ui->friend_name->setText(_friend_name);
    user_name = _user_name;
    friend_name = _friend_name;
    server = _server;
//    server = ServerInterface(user_name);
//    QTimer *timer = new QTimer(this);
    connect(&check_new_message, SIGNAL(timeout()), this, SLOT(CheckNewMessage()));
    check_new_message.start(1000);
}


void Chat::on_send_message_button_clicked()
{
    QString message_text = ui->user_message->toPlainText();
    ui->user_message->clear();
    AddNewMessage(message_text, this_user);
    server->SendMessage(message_text, friend_name, user_name);

}


Chat::Chat(){};


