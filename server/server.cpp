#include "server.h"
#include "fstream"
#include "message.h"
#include "workwithdatafile.h"
Server::Server(){
//  connection = Connection();
}

void Server::Next(){
  AddNewConnection();
  for (Client client : clients){
    std::string str_message = connection.Read(client.connection);
    if (!str_message.empty()){
      for (Message message : GetMessages(str_message, client.connection)){
        /*
        std::fstream file("log", std::ios::app);
        file << str_message;
        file << "\n";
        file.close();
        */
//        Message message(str_message, client.connection); /*= ParseMessage(str_message, client.connection);*/
        Send(message);
      }
    }
  }
}



void Server::Send(Message& message){

if (message.GetType() == Message::REGULAR){
    std::string who_send = message.GetWhomSend();
    Client client = FindUser(who_send);
    std::string ready_message = message.Formation()/*MessageFormation(message)*/;
    connection.Send(client.connection, ready_message);
}
  
if (message.GetType() == Message::BROKE_CONNECTION){
    /*
    std::string who_send = message.GetWhomSend();
    Client client = FindUser(who_send);
    std::string ready_message = message.Formation();
    connection.Send(client.connection, ready_message);
    */
   BrokeOldConnection(message.GetWhoSendSock());
}

if (message.GetType() == Message::GET_ALL_USERS){
    std::string users = WorkWithDataFile::GetAllUsers();
    connection.Send(message.GetWhoSendSock(), users);
}

if (message.GetType() == Message::GET_USERS_STATUS){
    std::string answer{'s'};
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
      else{
        name += c;
      }
    }
    connection.Send(message.GetWhoSendSock(), answer);
}

if (message.GetType() == Message::SET_USER_NAME){
  SetUserName(message);
}

}

void Server::SetUserName(Message& message){
  for (Client& client : clients){
    if(client.connection == message.GetWhoSendSock()){
      std::string new_name{message.GetText()};
      WorkWithDataFile::SetUserName(new_name, client.name);
      client.name = new_name;
    }
  }
}

Client Server::FindUser(std::string& name){
  for (Client client : clients){
    if (client.name == name){
      return client;
    }
  }
  return Client();
}

void Server::AddNewConnection(){
  int connect = connection.accept_new_connection();
  if (connect > 0){
/*    std::string name = connection.Read(connect);
    
    std::fstream file("log", std::ios::app);
    if (name.empty()){
      file << "empty name \n";
    }
    else{
       file << name.data();
       file << "\n";
    }
    file.close();
    
*/
    Client client;
    client.connection = connect;
    clients.push_back(client);
  }
}


void Server::BrokeOldConnection(int sock){

  for (size_t i=0; i<clients.size(); i++){
    if (clients[i].connection == sock){
      clients.erase(clients.begin()+i);
      break;
    }  
  }
}

bool Server::IsActiveUser(std::string& name){
  for (Client client : clients){
    if (client.name == name){
      return true;
    }
  }
  return false;
}


std::vector<Message> Server::GetMessages(std::string& str_message, int who_send_sock){
  std::vector<Message> messages;
  std::string message;
  int last_delemiter = 0;
  for (size_t i = 0; i < str_message.size()-2; i++)
  {
    if (IsMessageDelemiter(i, str_message)){
      messages.push_back(Message(str_message.substr(last_delemiter, i-last_delemiter), who_send_sock));
      last_delemiter = i + 3;
    }
  }
  return messages;
}

bool Server::IsMessageDelemiter(int i, std::string& str){
  return str[i] == '#' && str[i+1] == '?' && str[i+2] == '#';

}