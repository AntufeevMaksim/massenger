#include "serverinterface.h"


ServerInterface::ServerInterface(int user_id){
    SendUserId(user_id);
}

ServerInterface::ServerInterface(){}

void ServerInterface::SendUserId(int user_id){
    QString message = QString::number(user_id);
    message = 'i' + message;
    server = std::make_unique<Server>();
    server->SendMessage(message);
}

QString ServerInterface::Get_system_info(int friend_id, int user_id)
{
    QString system_info;
    system_info += "r";
    system_info += QString::number(friend_id);
    system_info += "|";
    system_info += QString::number(user_id);
    system_info += "|";
    return system_info;
}

void ServerInterface::SendMessage(QString& message, int friend_id, int user_id){
    QString ready_message = Get_system_info(friend_id, user_id);
    ready_message += message;
    server->SendMessage(ready_message);

}

QString ServerInterface::GetUserName(int id){
    using namespace std::chrono_literals;
    QString message("N");
    message += QString::number(id);
    server->SendMessage(message);

    QString answer;
    while (answer.isEmpty()){
        std::this_thread::sleep_for(100ms);
        for (size_t i=0; i<_messages.size(); i++){
            if (_messages[i].GetType() == Message::GET_USER_NAME){
                answer = _messages[i].GetText();
                _messages.erase(_messages.begin()+i);
                break;
            }
        }
        answer = ReadMessage(0, Message::GET_USER_NAME);
    }
    return answer;
}


QString ServerInterface::GetWhoSend(QString& message){
    QString who_send;
    for (QChar c : message){
        if (c == '|'){
            return who_send;
        }
        who_send.push_back(c);
    }
}

void ServerInterface::DeleteSystemInfo(QString& message){
    int i = 0;
      for (QChar c : message){
        if (c == '|'){
          message.remove(0, i+1);
          break;
        }
      i++;
      }
}


QString ServerInterface::ReadMessage(int friend_id, Message::TypeMessage type_message){
    QString s_message = server->ReadMessage();
    ParseMessage(s_message);
    for (size_t i=0; i < _messages.size(); i++){
        if (_messages[i].GetType() == type_message){
            if (type_message == Message::REGULAR && _messages[i].GetFriendId() == friend_id){
                QString text = _messages[i].GetText();
                _messages.erase(_messages.begin()+i);
                return text;
            }
            else if(type_message != Message::REGULAR){
                QString text = _messages[i].GetText();
                _messages.erase(_messages.begin()+i);
                return text;
            }
        }
    }
    return QString();
}

void ServerInterface::ParseMessage(QString& message){
    int last_delemiter = 0;
    for (int i = 0; i < message.size()-2; i++)
    {
      if (IsMessageDelemiter(i, message)){
        _messages.push_back(Message(message.mid(last_delemiter, i-last_delemiter)));
        last_delemiter = i + 3;
      }
   }
}

bool ServerInterface::IsMessageDelemiter(int i, QString& str){
  return str[i] == '#' && str[i+1] == '?' && str[i+2] == '#';

}











std::vector<QString> ServerInterface::GetAllUsers(){
    using namespace std::chrono_literals;
    std::vector<QString> all_users;
    QString answer;
    QString request{'g'};
    server->SendMessage(request);
    while (answer.isEmpty()){
        std::this_thread::sleep_for(100ms);
        for (size_t i=0; i<_messages.size(); i++){
            if (_messages[i].GetType() == Message::GET_ALL_USERS){
                answer = _messages[i].GetText();
                _messages.erase(_messages.begin()+i);
                break;
            }
        }
        answer = ReadMessage(0, Message::GET_ALL_USERS);
    }
    QString name;
    for (QChar c : answer){
        if (c == '\n'){
            all_users.push_back(name);
            name.clear();
        }
        else{
            name.push_back(c);
        }
    }

    all_users.push_back(name);
    return all_users;

}

int ServerInterface::GetUserId(){
    using namespace std::chrono_literals;

    QString answer;
    while (answer.isEmpty()){
        std::this_thread::sleep_for(100ms);
        for (size_t i=0; i<_messages.size(); i++){
            if (_messages[i].GetType() == Message::GET_USER_ID){
                answer = _messages[i].GetText();
                _messages.erase(_messages.begin()+i);
                break;
            }
        }
        answer = ReadMessage(0, Message::GET_USER_ID);

    }
    return answer.toInt();
}

QString ServerInterface::GetUsersStatus(QString &users){
    using namespace std::chrono_literals;
    users = "s" + users;
    server->SendMessage(users);
    QString answer;
        for (size_t i=0; i<_messages.size(); i++){
            if (_messages[i].GetType() == Message::GET_USERS_STATUS){
                answer = _messages[i].GetText();
                _messages.erase(_messages.begin()+i);
                return answer;
            }
        }
        answer = ReadMessage(0, Message::GET_USERS_STATUS);
    return answer;
}




void ServerInterface::BreakConnection(){
    QString b{'b'};
    server->SendMessage(b);
}

void ServerInterface::SendUsername(QString username){
    username = "n" + username;
    server->SendMessage(username);
}
