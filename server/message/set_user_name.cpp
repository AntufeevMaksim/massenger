#include "set_user_name.h"

SetUserName::SetUserName(std::string message, int sock, Server *server){
  _server = server;
  _who_send_sock = sock;
  Parse(message);
}

void SetUserName::Parse(std::string& message){
  message.erase(message.begin());
  _user_name = message;
}

void SetUserName::Send(){
  _server->SetUserName(_who_send_sock, _user_name);
}