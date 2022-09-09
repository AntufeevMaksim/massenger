#include "initialize_user.h"

InitializeUser::InitializeUser(std::string message, int sock, Server *server){
  _server = server;
  _who_send_sock = sock;

  message.erase(message.begin());
  _user_id = std::atoi(message.c_str());
}

void InitializeUser::Send(){
  _server->InitializeUser(_who_send_sock, _user_id);
}