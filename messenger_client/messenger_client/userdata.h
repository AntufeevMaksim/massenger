#ifndef LOADUSERDATA_H
#define LOADUSERDATA_H

#include <QListWidget>
#include <QListWidgetItem>

#include "usertype.h"
#include "serverinterface.h"

class UserData
{
public:
    static void LoadListFriends(QListWidget& users, ServerInterface *server);
    static void DeleteFriend(QListWidget &users, QListWidgetItem& user);
    static QString LoadUsername();
    static int LoadUserId();
    static void SetUsername(QString& username);
    static void AddNewFriend(QListWidgetItem* new_friend);
    static void AddNewMessage(int id, QString string_message, UserType& user_type);
    static void LoadChatHistory(QListWidget *chat, int id);
    static void SaveUserId(int user_id);
};

#endif // LOADUSERDATA_H
