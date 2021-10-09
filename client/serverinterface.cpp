#include "serverinterface.h"
#include <thread>
#include <chrono>
#include <poll.h>
#include <message.h>
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
    user_name = 'n' + user_name;
    server.SendMessage(user_name);
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


QString ServerInterface::ReadMessage(QString& friend_name){
    QString message = server.ReadMessage();
    if (!message.isEmpty()){

        if (QString(GetWhoSend(message).data()) == friend_name){
            DeleteSystemInfo(message);
            QString ready_message;
            /*
            for (char c : message){
                ready_message.append(c);
            }
            */
            return message /*QString(ready_message)*/;
        }
    }
    return QString();
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
        answer = server.ReadMessage();
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
    QString ready_answer;
    users = "s" + users;
//    std::string std_users = users.toStdString();
    server.SendMessage(users);
    QString answer;
    while (answer.isEmpty()){
        std::this_thread::sleep_for(100ms);
        answer = server.ReadMessage();
    }
    for (QChar c : answer){
        ready_answer.append(c);
    }
    return ready_answer;
}




void ServerInterface::BreakConnection(){
    QString b{'b'};
    server.SendMessage(b);
}












