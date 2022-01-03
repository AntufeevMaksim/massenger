#include "broke_connection.h"

BrokeConnection::BrokeConnection(std::string message, int sock, Server *server){
  _who_send_sock = sock;
  _server = server;
}

void BrokeConnection::Send(){
  _server->BrokeConnection(_who_send_sock);
}