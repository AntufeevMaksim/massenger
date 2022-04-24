#include "regular.h"
#include "server.h"
#include "client.h"
#include "workwithdatafile.h"
void Regular::Parse(std::string& message){
  message.erase(message.begin());
  int i = 0;
  std::string buf;
  for (char c : message){
    if (c == '|'){
      if (_whom_send.empty()){
        _whom_send = buf;
        buf.clear();
      }
      else if (_who_send.empty()){
        _who_send = buf;
        buf.clear();
      }
    }
    else{
      buf.push_back(c);
    }
    i++;
  }
  _text = buf;
}

std::string Regular::Formation(){
  std::string ready_message;
  ready_message += 'r';
  ready_message += _who_send;
  ready_message.push_back('|');
  for (char c : _text){
    ready_message.push_back(c);
  }
  return ready_message;
}


Regular::Regular(std::string message, int who_send_sock, Server *server){
  Parse(message);
  _who_send_sock = who_send_sock;
  _server = server;
}

void Regular::Send(){
  std::string ready_message = Formation();
  Client client = _server->FindUser(_whom_send);
  if (client.name == "&*^%Not&Found"){
    WorkWithDataFile::SaveMessageForOfflineUser(_whom_send, ready_message);
  }
  else{
    _server->Send(client.connection, ready_message);
  }
}