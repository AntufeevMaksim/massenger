#include "add_new_user.h"
#include "serverinterface.h"
#include "mainwindow.h"

void add_new_user::onListAllUsersClicked(QListWidgetItem* item,){
    QString name = item->text();
    QListWidgetItem *newItem = new QListWidgetItem;
    newItem->setText(name);
    friends->insertItem(1, newItem);
}



add_new_user::add_new_user(QWidget *parent, QListWidget* friends):QWidget(parent)
{
    all_users = new QListWidget(this);
    all_users->setGeometry(1, 1, 200, 500);

    std::vector<std::string> users = GetAllUsers();

    for (std::string& name :  users){
        QListWidgetItem *newItem = new QListWidgetItem;
        newItem->setText(name.c_str());
        all_users->insertItem(1, newItem);
        connect(&all_users, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(onListAllUsersClicked(QListWidgetItem*)));
    }
//    all_users->show();
}


add_new_user::~add_new_user(){
    delete all_users;
}


