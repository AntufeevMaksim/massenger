#ifndef MESSAGE_H
#define MESSAGE_H

#include <QString>

class Message
{
public:
    enum TypeMessage{
    REGULAR,
    GET_ALL_USERS,
    GET_USERS_STATUS,
    GET_USER_ID,
    GET_USER_NAME
    };
    Message(QString message);
    int GetFriendId();
    QString GetText();
    TypeMessage GetType();

private:
    void ParseRegularMessage(QString& message);
    int _friend_id;
    QString _text;
    TypeMessage _type;
};
#endif // MESSAGE_H
