#include "get_all_users.h"
#include "workwithdatafile.h"

GetAllUsers::GetAllUsers(std::string message, int sock, Server *server){
  _all_users = WorkWithDataFile::GetAllUsers();
  _who_send_sock = sock;
  _server = server;
}

void GetAllUsers::Send(){
  _server->Send(_who_send_sock, _all_users);
}

