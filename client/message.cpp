#include "message.h"

Message::Message(QString message)
{
    if (message[0] == 'r'){
        _type = REGULAR;
        message.remove(0, 1);
        ParseRegularMessage(message);
    }
    else if (message[0] == 'g'){
        _type = GET_ALL_USERS;
        message.remove(0, 1);
        _text = message;
    }
    else if (message[0] == 's'){
        _type = GET_USERS_STATUS;
        message.remove(0, 1);
        _text = message;
    }
}

void Message::ParseRegularMessage(QString& message){
    QString who_send;
    int i = 0;
    for (QChar c : message){
        if (c == '|'){
            message.remove(0, i+1);
            _friend_name = who_send;
        }
        who_send.push_back(c);
        i++;
    }
}

QString Message::GetFriendName(){
    return _friend_name;
}

QString Message::GetText(){
    return _text;
}

Message::TypeMessage Message::GetType(){
    return _type;
}

