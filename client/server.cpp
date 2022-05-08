#include "server.h"
#include "workwithdatafile.h"
#include "message/message_creator.h"
Server::Server(){
}

void Server::Next(){
  AddNewConnection();
  for (Client client : clients){
    std::string str_message = connection.Read(client.connection);
    if (!str_message.empty()){
      std::vector<std::string> messages = GetMessages(str_message);
      for (std::string& str_message : messages){
        Message* message = MessageCreator::New(str_message, client.connection, this);
        message->Send();
        delete message;
      }
    }
  }
}

void Server::SetUserName(int sock, std::string& name){
  for (Client& client : clients){
    if(client.connection == sock){
      WorkWithDataFile::SetUserName(name, client.name);
      client.name = name;
    }
  }
  SendSavedMessages(sock, name);
  
}



void Server::SendSavedMessages(int sock, std::string& name){
  std::vector<std::string> saved_messages = WorkWithDataFile::GetSavedMessages(name);

  for (std::string message : saved_messages){
    Send(sock, message);
  }
}


void Server::Send(int sock, std::string& message){
  connection.Send(sock, message);
}

Client Server::FindUser(std::string& name){
  for (Client client : clients){
    if (client.name == name){
      return client;
    }
  }
  Client client;
  client.name = "&*^%Not&Found"; 
  return client;
}

void Server::AddNewConnection(){
  int connect = connection.accept_new_connection();
  if (connect > 0){
    Client client;
    client.connection = connect;
    clients.push_back(client);
  }
}


void Server::BrokeConnection(int sock){
  for (size_t i=0; i<clients.size(); i++){
    if (clients[i].connection == sock){
      clients.erase(clients.begin()+i);
      break;
    }  
  }
}

std::vector<std::string> Server::GetOnlineUsersNames(){
  std::vector<std::string> names;
  for(Client& client : clients){
    names.push_back(client.name);
  }
  return names;
}






std::vector<std::string> Server::GetMessages(const std::string& message){
  std::vector<std::string> messages;
  int last_delemiter = 0;
  for (size_t i = 0; i < message.size()-2; i++)
  {
    if (IsMessageDelemiter(i, message)){
      messages.push_back(message.substr(last_delemiter, i-last_delemiter));
      last_delemiter = i + 3;
    }
  }
  return messages;
}


bool Server::IsMessageDelemiter(int i, const std::string& str){
  return str[i] == '#' && str[i+1] == '?' && str[i+2] == '#';
}
