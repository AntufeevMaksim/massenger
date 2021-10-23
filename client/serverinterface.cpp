#include "serverinterface.h"
#include <thread>
#include <chrono>
#include <poll.h>
/*
Client::Client(std::vector<char>& name, std::vector<char>& message){
    _message = message;
    _name = name;
}

std::vector<char> Client::GetName(){
    return _name;
}

std::vector<char> Client::GetMessage(){
    return _message;
}

void Client::ClearMessage(){
    _message.clear();
}

void Client::AddMessage(std::vector<char>& message){
    _message.push_back('/n');
    for (char c : message){
        _message.push_back(c);
    }
}
*/
/*
ServerInterface::~ServerInterface(){
    std::vector<char> std_user_name;
    std_user_name.push_back('b');
    for (char c : user_name){
        std_user_name.push_back(c);
    }
    server.BreakConnection(std_user_name);
}
*/



ServerInterface::ServerInterface(QString user_name){

//    server = Server();
//    std::string std_user_name = "n" + user_name.toStdString();
    SendUsername(user_name);
}




QString ServerInterface::Get_system_info(QString& friend_name, QString& user_name)
{
    QString system_info;
    system_info += "r";
    system_info += friend_name;
    system_info += "|";
    system_info += user_name;
    system_info += "|";

    return system_info;
}

void ServerInterface::SendMessage(QString& message, QString& friend_name, QString& user_name){
    QString ready_message = Get_system_info(friend_name, user_name);
    ready_message += message;
//    std_message += message.toStdString();

    server.SendMessage(ready_message);

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


QString ServerInterface::ReadMessage(QString& friend_name, Message::TypeMessage type_message){
    QString s_message = server.ReadMessage();
    ParseMessage(s_message);
    for (size_t i=0; i < _messages.size(); i++){
        if (_messages[i].GetType() == type_message){
            if (type_message == Message::REGULAR && _messages[i].GetFriendName() == friend_name){
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

/*
    if (!s_message.isEmpty()){
        Message message(s_message);
        if (message.GetType() == type_message){
            if (type_message == Message::REGULAR && message.GetFriendName() == friend_name){
                return message.GetText();
            }
            else if(type_message != Message::REGULAR)
                return message.GetText();
        }
        else{
            _messages.push_back(message);
        }
    }
*/
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


ServerInterface::ServerInterface(){}










std::vector<QString> ServerInterface::GetAllUsers(){
    using namespace std::chrono_literals;
    std::vector<QString> all_users;

//    all_users.push_back(std::string("Maksim"));
//    all_users.push_back(std::string("Ne Maksim"));
    QString answer;
    QString request{'g'};
    server.SendMessage(request);
    while (answer.isEmpty()){
        std::this_thread::sleep_for(100ms);
        for (size_t i=0; i<_messages.size(); i++){
            if (_messages[i].GetType() == Message::GET_ALL_USERS){
                answer = _messages[i].GetText();
                _messages.erase(_messages.begin()+i);
                break;
            }
        }
        QString s;
        answer = ReadMessage(s, Message::GET_ALL_USERS);
//        answer = server.ReadMessage();
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

QString ServerInterface::GetUsersStatus(QString &users){
    using namespace std::chrono_literals;
    users = "s" + users;
    server.SendMessage(users);
    QString answer;
//    while (answer.isEmpty()){
//        std::this_thread::sleep_for(100ms);
        for (size_t i=0; i<_messages.size(); i++){
            if (_messages[i].GetType() == Message::GET_USERS_STATUS){
                answer = _messages[i].GetText();
                _messages.erase(_messages.begin()+i);
                return answer;
            }
        }
        QString a;
        answer = ReadMessage(a, Message::GET_USERS_STATUS);
//    }
    return answer;
}




void ServerInterface::BreakConnection(){
    QString b{'b'};
    server.SendMessage(b);
}

void ServerInterface::SendUsername(QString username){
    username = "n" + username;
    server.SendMessage(username);
}












