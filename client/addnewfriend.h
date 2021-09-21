#ifndef ADDNEWFRIEND_H
#define ADDNEWFRIEND_H

#include <QMainWindow>
#include <QListWidget>
//#include <mainwindow.h>
#include "ui_addnewfriend.h"
#include <memory>
#include "serverinterface.h"

namespace Ui {
class AddNewFriend;
}

class AddNewFriend : public QMainWindow
{
    Q_OBJECT

public:
    explicit AddNewFriend(QWidget *parent, QListWidget* _friend,  ServerInterface *_server);


private:
    std::unique_ptr<Ui::AddNewFriend> ui = std::make_unique<Ui::AddNewFriend>();
    std::unique_ptr<QListWidget> friends;
    void GetAllUsers();
    ServerInterface *server;

private slots:
    void onListallUsersClicked(QListWidgetItem* item);


};

#endif // ADDNEWFRIEND_H
