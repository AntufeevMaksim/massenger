#include "server.h"
#include "fstream"
#include "message.h"

Server::Server(){
//  connection = Connection();
}

void Server::Next(){
  AddNewConnection();
  for (Client client : clients){
    std::vector<char> str_message = connection.Read(client.connection);
    if (!str_message.empty()){
      std::fstream file("log", std::ios::app);
       file << str_message.data();
       file << "\n";
      file.close();
      Message message(str_message, client.connection); /*= ParseMessage(str_message, client.connection);*/
      Send(message);
    }
  }
}



void Server::Send(Message& message){

if (message.GetType() == Message::REGULAR){
    std::vector<char> who_send = message.GetWhomSend();
    Client client = FindUser(who_send);
    std::vector<char> ready_message = message.Formation()/*MessageFormation(message)*/;
    connection.Send(client.connection, ready_message);
}
  
if (message.GetType() == Message::BROKE_CONNECTION){
    std::vector<char> who_send = message.GetWhomSend();
    Client client = FindUser(who_send);
    std::vector<char> ready_message = message.Formation();
    connection.Send(client.connection, ready_message);
}

if (message.GetType() == Message::GET_ALL_USERS){
    std::string users;
    std::string line;
    std::fstream file("users");
    while(getline(file, line)){
      users += line += "\n";
    }
    file.close();
    connection.Send(message.GetWhoSendSock(), users);
}

if (message.GetType() == Message::GET_USERS_STATUS){
    std::string answer;
    std::string name;
    for (char c : message.GetText()){
      if (c == '\n'){
        if (IsActiveUser(name)){
          answer += "1";
        }
        else{
          answer += "0";
        }
        name.clear();
      }
      name += c;
    }
    connection.Send(message.GetWhoSendSock(), answer);
}
/*
  if (message.GetType() == Message::REGULAR){
    std::vector<char> who_send = message.GetWhomSend();
    Client client = FindUser(who_send);
    std::vector<char> ready_message = message.Formation();
    connection.Send(client.connection, ready_message);
  }
  if (message.GetType() == Message::BROKE_CONNECTION){
//    std::vector<char> who_send = message.GetWhomSend();
    BrokeOldConnection(message.GetWhoSendSock());
  }
  if (message.GetType() == Message::GET_ALL_USERS){
    std::string users;
    std::string line;
    std::fstream file("users");
    while(getline(file, line)){
      users += line += "\n";
    }
    file.close();
    connection.Send(message.GetWhoSendSock(), users);


  }
*/

}

Client Server::FindUser(std::vector<char>& name){
  for (Client client : clients){
    if (client.name == name){
      return client;
    }
  }
}

void Server::AddNewConnection(){
  int connect = connection.accept_new_connection();
  if (connect > 0){
    std::vector<char> name = connection.Read(connect);
    
    std::fstream file("log", std::ios::app);
    if (name.empty()){
      file << "empty name \n";
    }
    else{
       file << name.data();
       file << "\n";
    }
    file.close();
    
//    BrokeOldConnection(name);
//    DeleteOldConnection(clients, name);
    Client client;
    client.name = name;
    client.connection = connect;
    clients.push_back(client);
  }
}


void Server::BrokeOldConnection(int sock){

  for (int i=0; i<clients.size(); i++){
    if (clients[i].connection == sock){
      clients.erase(clients.begin()+i);
      break;
    }  
  }
}

bool Server::IsActiveUser(std::string name){
  std::vector<char> vec_name;
  for (char c : name){
    vec_name.push_back(c);
  }
  for (Client client : clients){
    if (client.name == vec_name){
      return true;
    }
  }
  return false;
}

