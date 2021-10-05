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
      Message message(str_message, client.connection); /*= ParseMessage(str_message, client.connection);*/
      Send(message);
    }
  }
}



/*
Message Server::ParseMessage(std::vector<char>& message, int who_send_sock){
  Message ready_message;
  if (message[0] == 'r'){
    message.erase(message.begin());
    ready_message = ParseRegularMessage(message);
    ready_message.type = Message::REGULAR;
    return ready_message;
  }
  if (message[0] == 'g' ){
    ready_message.type = Message::GET_ALL_USERS;
    ready_message.who_send_sock = who_send_sock;
    return ready_message;
  }
  if (message[0] == 'b'){
    ready_message.type = Message::BROKE_CONNECTION;
    message.erase(message.begin());
    ready_message.who_send = message;
  }
}

Message Server::ParseRegularMessage(std::vector<char>& message){
  int i = 0;
  std::vector<char> buf;
  Message ready_message;
  for (char c : message){
    if (c == '|'){
      if (ready_message.whom_send.empty()){
        ready_message.whom_send = buf;
        buf.clear();
      }
      else if (ready_message.who_send.empty()){
        ready_message.who_send = buf;
        buf.clear();
      }
    }
    else{
      buf.push_back(c);
    }
    i++;
  }
  ready_message.text = buf;
  return ready_message;

}

std::vector<char> Server::MessageFormation(Message& message){
  std::vector<char> ready_message;
  if (message.GetType() == Message::REGULAR){
    ready_message = message.GetWhoSend();
    ready_message.push_back('|');
    for (char c : message.GetText()){
      ready_message.push_back(c);
    }
  }
  return ready_message;
}

*/
void Server::Send(Message& message){


  if (message.GetType() == Message::REGULAR){
    std::vector<char> who_send = message.GetWhomSend();
    Client client = FindUser(who_send);
    std::vector<char> ready_message = message.Formation()/*MessageFormation(message)*/;
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

