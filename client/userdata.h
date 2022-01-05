#ifndef LOADUSERDATA_H
#define LOADUSERDATA_H

#include <QListWidget>
#include <QListWidgetItem>
#include "usertype.h"
class UserData
{
public:
    static void LoadListFriends(QListWidget& users);
    static void DeleteFriend(QListWidget &users, QListWidgetItem& user);
    static QString LoadUsername();
    static void SetUsername(QString& username);
    static void AddNewFriend(QString& str_name);
    static void AddNewMessage(QString& username, QString string_message, UserType& user_type);
    static void LoadChatHistory(QListWidget *chat, QString &username);
};

#endif // LOADUSERDATA_H
