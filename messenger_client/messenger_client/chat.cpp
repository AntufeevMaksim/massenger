#include "chat.h"
#include "userdata.h"

void Chat::CheckNewMessage(){
    QString message = server->ReadMessage(_friend_id, Message::REGULAR);
    if (!message.isEmpty()){
        AddNewMessage(message, friend_user);
    }
}


void Chat::AddNewMessage(QString& text, UserType user_type){
    QListWidgetItem *new_message = new QListWidgetItem;
    new_message->setText(text);
    if (user_type == this_user){
        new_message->setBackground(Qt::green);
    }
    ui->user_chat->addItem(new_message);
    UserData::AddNewMessage(_friend_id, text, user_type);

}





Chat::Chat(QWidget *parent, int user_id, int friend_id, QString& friend_name, ServerInterface *_server) :
    QMainWindow(parent)
{
    ui->setupUi(this);
    ui->friend_name->setText(_server->GetUserName(friend_id));
    _user_id = user_id;
    _friend_id = friend_id;
    _friend_name = friend_name;
    server = _server;
    connect(&check_new_message, SIGNAL(timeout()), this, SLOT(CheckNewMessage()));
    UserData::LoadChatHistory(ui->user_chat, _friend_id);
    check_new_message.start(1000);
}


void Chat::on_send_message_button_clicked()
{
    QString message_text = ui->user_message->toPlainText();
    ui->user_message->clear();
    AddNewMessage(message_text, this_user);
    server->SendMessage(message_text, _friend_id, _user_id);

}


Chat::Chat(){};


