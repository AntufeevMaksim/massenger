#include "mainwindow.h"
#include "addnewfriend.h"
#include "serverinterface.h"
#include <stdio.h>
#include <QObject>
#include "chat.h"
#include <fstream>
void MainWindow::onListMailItemClicked(QListWidgetItem* item)
{
    QString friend_name = item->text();
    user_chat.reset(new Chat(0, user_name, friend_name, &server));
    user_chat->show();
}

void MainWindow::onListMailItemDoubleClicked(QListWidgetItem *item){
    delete ui->friends->takeItem(ui->friends->row(item));

}

void MainWindow::CheckFriendsStatus(){
    QString all_friends;
    for (int i = 0; i < ui->friends->count(); ++i){
//        all_friends += ui->friends->takeItem(i)->text() + "\n";
    }
    QString friens_status = server.GetUsersStatus(all_friends);
/*
    for (int i = 0; i < friens_status.size(); ++i) {
        if (friens_status[i] == "1"){
            ui->friends->takeItem(i)->setBackground(Qt::green);
        }
        else{
           ui->friends->takeItem(i)->setBackground(Qt::red);
        }
    }
*/
}




void MainWindow::LoadListFriends(){
    std::string name;
    std::fstream file("my_friends");
    while(getline(file, name)){
        if (!name.empty()){
            QListWidgetItem *user = new QListWidgetItem();
            user->setText(name.c_str());
            ui->friends->addItem(user);
        }
    }
    file.close();
}



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
//    user_name = "test_user_name";
//    user_name = "Maksim";
    user_name = "Ne Maksim";
    ui->setupUi(this);
    LoadListFriends();
    connect(ui->friends, SIGNAL(itemDoubleClicked(QListWidgetItem*)),
                this, SLOT(onListMailItemDoubleClicked(QListWidgetItem*)));

    connect(ui->friends, SIGNAL(itemClicked(QListWidgetItem*)),
                this, SLOT(onListMailItemClicked(QListWidgetItem*)));

    server = ServerInterface(user_name);
//    connect(&check_friends_status, SIGNAL(timeout()), this, SLOT(CheckFriendsStatus()));
//    check_friends_status.start(1000);

}




//QListWidgetItem *newItem = new QListWidgetItem;
//newItem->setText("newitem");
//connect(ui->Friends, SIGNAL(itemClicked(QListWidgetItem*)),
//            this, SLOT(onListMailItemClicked(QListWidgetItem*)));
//
//ui->Friends->insertItem(1, newItem);


void MainWindow::on_actionAdd_user_triggered()
{
    add_new_friend_window.reset(new AddNewFriend(0, ui->friends, &server));
    add_new_friend_window->show();
}


void MainWindow::closeEvent(QCloseEvent*/*event*/){
    server.BreakConnection();
}












