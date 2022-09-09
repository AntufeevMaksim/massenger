#include "addnewfriend.h"
#include "serverinterface.h"
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
   for (QString& str_user : name_all_users){
       User user = Parse(str_user);
       QListWidgetItem *user_item = new QListWidgetItem;
       QVariant user_id;
       user_id.setValue(user.id);
       user_item->setData(Qt::UserRole, user_id);
       user_item->setText(user.name);
       ui->list_all_users->addItem(user_item);
   }
}




void AddNewFriend::onListallUsersClicked(QListWidgetItem* item){
    QString name = item->text();
    QListWidgetItem *new_friend = new QListWidgetItem;
    new_friend->setText(name);
    new_friend->setData(Qt::UserRole, item->data(Qt::UserRole));
    friends->addItem(new_friend);
    UserData::AddNewFriend(name);
}

User AddNewFriend::Parse(QString &user){
    User output;
    QString id;
    for (int i = 0; i < user.size(); i++){
        if (!IsDelimiter(user, i)){
            id += user[i];
        }
        else{
            user.remove(0, i+3);
            output.name = user;
            break;
        }
    }
    output.id = id.toInt();
    return output;
}

bool AddNewFriend::IsDelimiter(QString& str, int i){
    if (str[i] == "~" & str[i+1] == "&" & str[i+2] == "~"){
        return true;
    }
    return false;
}
