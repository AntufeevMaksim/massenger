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



ServerInterface::ServerInterface(QString& user_name){

//    server = Server();
    std::string std_user_name = "n" + user_name.toStdString();

    server.SendMessage(std_user_name);
}




std::string ServerInterface::Get_system_info(QString& friend_name, QString& user_name)
{
    std::string system_info;
    system_info += "r";
    system_info += friend_name.toStdString();
    system_info += "|";
    system_info += user_name.toStdString();
    system_info += "|";

    return system_info;
}

void ServerInterface::SendMessage(QString& message, QString& friend_name, QString& user_name){
    std::string std_message = Get_system_info(friend_name, user_name);

    std_message += message.toStdString();

    server.SendMessage(std_message);

}

std::vector<char> ServerInterface::GetWhoSend(std::vector<char>& message){
    std::vector<char> who_send;
    for (char c : message){
        if (c == '|'){
            return who_send;
        }
        who_send.push_back(c);
    }
}

void ServerInterface::DeleteSystemInfo(std::vector<char>& message){
    int i = 0;
      for (char c : message){
        if (c == '|'){
          message.erase(message.begin(), message.begin() + i+1);
          break;
        }
      i++;
      }
}

/*
void ServerInterface::AddNewMessage(std::vector<char>& who_send, std::vector<char>& message){
    for (Client client : clients){
        if (client.GetName() == who_send){
            client.AddMessage(message);
        }
    }

    Client client(who_send, message);
    clients.push_back(client);
}
*/




/*
void ServerInterface::ReadMessage(){
    std::vector<char> message = Read(sock);
    if (!message.empty()){
        std::vector<char> who_send = GetWhoSend(message);
        DeleteSystemInfo(message);
        AddNewMessage(who_send, message);
    }
}
*/



QString ServerInterface::ReadMessage(QString& friend_name){
    std::vector<char> message = server.ReadMessage();
    if (!message.empty()){
        if (QString(GetWhoSend(message).data()) == friend_name){
            DeleteSystemInfo(message);
            QString ready_message;
            for (char c : message){
                ready_message.append(c);
            }
            return QString(ready_message);
        }
    }
    return QString();
}




ServerInterface::ServerInterface(){}










std::vector<std::string> ServerInterface::GetAllUsers(){
    using namespace std::chrono_literals;
    std::vector<std::string> all_users;

//    all_users.push_back(std::string("Maksim"));
//    all_users.push_back(std::string("Ne Maksim"));
    std::vector<char> answer;
    std::string request{'g'};
    server.SendMessage(request);
    while (answer.empty()){
        std::this_thread::sleep_for(100ms);
        answer = server.ReadMessage();
    }
    std::string name;
    for (char c : answer){
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
    std::string std_users = users.toStdString();
    server.SendMessage(std_users);
    std::vector<char> answer;
    while (answer.empty()){
        std::this_thread::sleep_for(100ms);
        answer = server.ReadMessage();
    }
    for (char c : answer){
        ready_answer.append(c);
    }
    return ready_answer;
}




void ServerInterface::BreakConnection(){
    std::string b{"b"};
    server.SendMessage(b);
}












