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
    };
    Message(QString message);
    QString GetFriendName();
    QString GetText();
    TypeMessage GetType();

private:
    void ParseRegularMessage(QString& message);
    QString _friend_name;
    QString _text;
    TypeMessage _type;
};
#endif // MESSAGE_H
