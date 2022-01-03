#include "get_users_status.h"

void GetUsersStatus::Parse(std::string& message){
  message.erase(message.begin());
  std::string name;
  for (char c : message){
    if (c == '\n'){
      _users_names.push_back(name);
      name.clear();
    }
    else{
      name += c;
    }
  }  
}




GetUsersStatus::GetUsersStatus(std::string message, int sock, Server *server){
  Parse(message);
  _who_send_sock = sock;
  _server = server;
}


void GetUsersStatus::Send(){
  std::string answer{'s'};
  std::vector<std::string> online_users = _server->GetOnlineUsersNames();

  for(std::string& name : _users_names){
    bool this_user_online = false;
    for(std::string& online_user : online_users){
      if(name == online_user){
        this_user_online = true;
      }
    }
    if(this_user_online){
      answer += '1';
    }
    else{
      answer += '0';
    }
  }
  _server->Send(_who_send_sock, answer);
}