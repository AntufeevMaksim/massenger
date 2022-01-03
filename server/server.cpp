#include "server.h"
#include "fstream"
#include "workwithdatafile.h"
#include "message/message.h"
Server::Server(){
//  connection = Connection();
}

void Server::Next(){
  AddNewConnection();
  for (Client client : clients){
    std::string str_message = connection.Read(client.connection);
    if (!str_message.empty()){
    std::fstream file("log", std::ios::app);
    file << str_message;
    file << "\n--------------\n";
    file.close();
      std::vector<std::string> messages = GetMessages(str_message);
      if(str_message.find("XUUU") != std::string::npos){
        printf("%s", str_message.c_str());
      }
      for (std::string& str_message : messages){
//        std::unique_ptr<Message> message;
//        message.reset(Message::New(str_message, client.connection, this));
        Message* message = Message::New(str_message, client.connection, this);
        message->Send();
        delete message;
        /*
        std::fstream file("log", std::ios::app);
        file << str_message;
        file << "\n";
        file.close();
        */
//        Send(message);
      }
    }
  }
}


/*
void Server::Send(Message& message){

if (message.GetType() == Message::REGULAR){
    std::string who_send = message.GetWhomSend();
    std::string whom_send = message.GetWhomSend();
    Client client = FindUser(who_send);
    std::string ready_message = message.Formation();

    if(IsActiveUser(whom_send)){
      connection.Send(client.connection, ready_message);
    }
    else{
      WorkWithDataFile::AddMessage(whom_send, message.GetText())
    }
}
  
if (message.GetType() == Message::BROKE_CONNECTION){
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
*/

void Server::SetUserName(int sock, std::string& name){
  for (Client& client : clients){
    if(client.connection == sock){
      WorkWithDataFile::SetUserName(name, client.name);
      client.name = name;
    }
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
  return Client();
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

/*
bool Server::IsActiveUser(std::string& name){
  for (Client client : clients){
    if (client.name == name){
      return true;
    }
  }
  return false;
}

*/

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
//      auto message = std::make_unique<Message>(str_message.substr(last_delemiter, i-last_delemiter), who_send_sock);
//      messages.push_back(std::move(message));
      messages.push_back(message.substr(last_delemiter, i-last_delemiter));
      last_delemiter = i + 3;
    }
  }
  return messages;
}


bool Server::IsMessageDelemiter(int i, const std::string& str){
  return str[i] == '#' && str[i+1] == '?' && str[i+2] == '#';
}
