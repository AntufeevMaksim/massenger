#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QString>
#include "serverinterface.h"
#include "chat.h"
#include "ui_mainwindow.h"
#include "addnewfriend.h"
#include "ui_addnewfriend.h"
#include <QCloseEvent>
#include <QTimer>
#include <setusername.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow;}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private slots:
    void onListMailItemClicked(QListWidgetItem* item);
    void onListMailItemDoubleClicked(QListWidgetItem* item);
    void on_actionAdd_user_triggered();
    void on_actionSet_username_triggered();
    void CheckFriendsStatus();

private:
    void closeEvent(QCloseEvent *event);
    std::unique_ptr<Ui::MainWindow> ui = std::make_unique<Ui::MainWindow>();
    std::unique_ptr<AddNewFriend> add_new_friend_window;
    std::unique_ptr<Chat> user_chat;
    std::unique_ptr<SetUsername> set_username;
    std::unique_ptr<ServerInterface> server_interface;
//    ServerInterface server;
    QString user_name;
    int _user_id;
    Chat chat;
    QTimer check_friends_status;

};
#endif // MAINWINDOW_H
