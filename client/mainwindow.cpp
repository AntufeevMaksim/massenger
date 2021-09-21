#include "mainwindow.h"
#include "addnewfriend.h"
#include "serverinterface.h"
#include <stdio.h>
#include <QObject>
#include "chat.h"

void MainWindow::onListMailItemClicked(QListWidgetItem* item)
{
    QString friend_name = item->text();
    user_chat.reset(new Chat(0, user_name, friend_name, &server));
    user_chat->show();
}



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
//    user_name = "test_user_name";
//    user_name = "Maksim";
    user_name = "Ne Maksim";
    ui->setupUi(this);
    connect(ui->friends, SIGNAL(itemClicked(QListWidgetItem*)),
                this, SLOT(onListMailItemClicked(QListWidgetItem*)));
    server = ServerInterface(user_name);

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














