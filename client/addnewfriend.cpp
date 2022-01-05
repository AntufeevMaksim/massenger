#include "addnewfriend.h"
#include "serverinterface.h"
#include <QListWidgetItem>
#include "mainwindow.h"
#include <fstream>
#include "userdata.h"
AddNewFriend::AddNewFriend(QWidget *parent, QListWidget* _friend, ServerInterface *_server):
    QMainWindow(parent)
{
    server = _server;
    ui->setupUi(this);
    friends = _friend;
    GetAllUsers();
    connect(ui->list_all_users, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(onListallUsersClicked(QListWidgetItem*)));
}




void AddNewFriend::GetAllUsers(){
   std::vector<QString> name_all_users = server->GetAllUsers();
   for (QString& name : name_all_users){
       QListWidgetItem *user = new QListWidgetItem;
       user->setText(name);
       ui->list_all_users->addItem(user);
   }
}




void AddNewFriend::onListallUsersClicked(QListWidgetItem* item){
    QString name = item->text();
    QListWidgetItem *new_friend = new QListWidgetItem;
    new_friend->setText(name);
    friends->addItem(new_friend);
    UserData::AddNewFriend(name);
}
