#ifndef LOADUSERDATA_H
#define LOADUSERDATA_H

#include <QListWidget>
#include <QListWidgetItem>

class UserData
{
public:
    static void LoadListFriends(QListWidget& users);
    static void DeleteFriend(QListWidget &users, QListWidgetItem& user);
    static QString LoadUsername();
    static void SetUsername(QString& username);
    static void AddNewFriend(QString& name);
    static void AddNewMessage(QString& username, QString& message);
};

#endif // LOADUSERDATA_H
