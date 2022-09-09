#include "get_users_status.h"

void GetUsersStatus::Parse(std::string& message){
  message.erase(message.begin());
  std::string id;
  for (char c : message){
    if (c == '\n'){
      _users_id.push_back(atoi(id.c_str()));
      id.clear();
    }
    else{
      id += c;
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
  std::vector<int> online_users = _server->GetOnlineUsersId();

  for(int id : _users_id){
    bool this_user_online = false;
    for(int online_user : online_users){
      if(id == online_user){
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