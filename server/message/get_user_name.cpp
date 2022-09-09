#include "get_user_name.h"

#include "client.h"
#include "workwithdatafile.h"

GetUserName::GetUserName(std::string message, int sock, Server *server){
  _who_send_sock = sock;
  _server = server;
  message.erase(message.begin());
  int id = atoi(message.c_str());
  std::string user = WorkWithDataFile::GetUserName(id);
  _answer = "N" + user;
}

void GetUserName::Send(){
  _server->Send(_who_send_sock, _answer);
}
