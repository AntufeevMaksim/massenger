#include "mainwindow.h"
#include "userdata.h"

void MainWindow::on_actionSet_username_triggered(){
    set_username.reset(new SetUsername(0, &user_name, &server));
    set_username->show();
}



void MainWindow::onListMailItemClicked(QListWidgetItem *item)
{
    QVariant data = item->data(Qt::UserRole);
    int friend_id = data.toInt();
    QString friend_name = item->text();
    user_chat.reset(new Chat(0, _user_id, friend_id, friend_name, &server));
    user_chat->show();
}

void MainWindow::onListMailItemDoubleClicked(QListWidgetItem *item){
    UserData::DeleteFriend(*(ui->friends), *item);
}

void MainWindow::CheckFriendsStatus(){
    /*
    QString all_friends;
    for (int i = 0; i < ui->friends->count(); ++i){
        QVariant data = ui->friends->item(i)->data(Qt::UserRole);
        int id = data.toInt();
        all_friends += QString::number(id) + "\n";
    }
    QString friens_status = server.GetUsersStatus(all_friends);
    if(friens_status.isEmpty()){
        return;
    }

    for (int i = 0; i < ui->friends->count(); ++i) {
        if (friens_status[i] == "1"){
            ui->friends->item(i)->setBackground(Qt::green);
        }
        else{
           ui->friends->item(i)->setBackground(Qt::red);
        }
    }
*/
}




MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    user_name = UserData::LoadUsername();
    _user_id = UserData::LoadUserId();
    ui->setupUi(this);
    server = ServerInterface(_user_id);
    UserData::LoadListFriends(*(ui->friends),&server);
    connect(ui->friends, SIGNAL(itemDoubleClicked(QListWidgetItem*)),
                this, SLOT(onListMailItemDoubleClicked(QListWidgetItem*)));

    connect(ui->friends, SIGNAL(itemClicked(QListWidgetItem*)),
                this, SLOT(onListMailItemClicked(QListWidgetItem*)));

    server = ServerInterface(_user_id);
    if (_user_id == 0){
        _user_id = server.GetUserId();
        UserData::SaveUserId(_user_id);
    }
    server.SendUsername(user_name);
    connect(&check_friends_status, SIGNAL(timeout()), this, SLOT(CheckFriendsStatus()));
    check_friends_status.start(1000);

}




void MainWindow::on_actionAdd_user_triggered()
{
    add_new_friend_window.reset(new AddNewFriend(0, ui->friends, &server));
    add_new_friend_window->show();
}


void MainWindow::closeEvent(QCloseEvent*){
    server.BreakConnection();
}












