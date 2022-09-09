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

void Server::ChangeUserName(int sock, std::string& name){
  for (Client& client : clients){
    if(client.connection == sock){
      WorkWithDataFile::ChangeUserName(client.id, name);
      client.name = name;
      break;
    }
  }  
}

void Server::InitializeUser(int sock, int user_id){
  for (Client& client : clients){
    if(client.connection == sock){
      if (user_id > 0){ //already exists user
        client.id = user_id;
        SendSavedMessages(sock, client.id);
      }
      else{ //new user
        int new_id = WorkWithDataFile::GetNewId();
        WorkWithDataFile::CreateNewUser(new_id);
        client.id = new_id;
        
        std::string message("d");
        message += std::to_string(new_id);
        Send(client.connection, message);
      }
    }
  }
  
}

void Server::SendSavedMessages(int sock, int user_id){
  std::vector<std::string> saved_messages = WorkWithDataFile::GetSavedMessages(user_id);

  for (std::string message : saved_messages){
    Send(sock, message);
  }
}


void Server::Send(int sock, std::string& message){
  connection.Send(sock, message);
}

Client Server::FindUser(int user_id){
  for (Client client : clients){
    if (client.id == user_id){
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

std::vector<int> Server::GetOnlineUsersId(){
  std::vector<int> id;
  for(Client& client : clients){
    id.push_back(client.id);
  }
  return id;
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
