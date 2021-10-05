/*
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <poll.h>
#include <sys/ioctl.h>
#include <vector>
#include <fcntl.h>
#include <algorithm>

struct Client
{
  std::vector<char> name;
  int connection;
};


struct SystemInfo{
  std::vector<char> who_send;
  std::vector<char> whom_send;
};



SystemInfo GetSystemInfo(std::vector<char>& message){
  std::vector<char> buf;
  int i = 0;
  SystemInfo system_info;
  for (char c : message){
    if (c == '|'){
      if (system_info.whom_send.empty()){
        system_info.whom_send = buf;
        buf.clear();
      }
      else if (system_info.who_send.empty()){
        system_info.who_send = buf;
        buf.clear();
      }
      else{
        break;
      }
    }
    else{
      buf.push_back(c);
    }
    i++;
  }
  return system_info;
}



std::vector<char> Read(int s){
  fd_set readfs;
  FD_ZERO(&readfs);
  FD_SET(s, &readfs);

  struct timeval tv;
  tv.tv_sec = 1;
  tv.tv_usec = 100;

  int n;
  unsigned int m;

  int res = select(s+1, &readfs, NULL, NULL, &tv);
//  int rc = recv(s, buf.data(), 3, 0);
  if (res>0){
    ioctl(s, TIOCINQ, &n);
    std::vector<char> buf(n);
    int rc = recv(s, buf.data(), n, 0);
    return (rc == 0 ? std::vector<char>{} : buf);
  }
  else{
    return {};
  }
}

void Send(int sock, std::vector<char> buf){
  if (!buf.empty()){
    send(sock, buf.data(), buf.size(), 0);
  }
}


int WhomSend(std::vector<char>& message, std::vector<Client>& clients){
  SystemInfo message_info = GetSystemInfo(message);
  for (Client client : clients){
    if (client.name == message_info.whom_send){
      return client.connection;
    }
  }
}

void PreparationForSending(std::vector<char>& message){
//  int number_separators = 0;
  int i = 0;
    for (char c : message){
      if (c == '|'){
//        number_separators += 1;
//      }
//      if (number_separators == 2){
        message.erase(message.begin(), message.begin() + i+1);
        break;
      }
    i++;
    }
}


void DeleteOldConnection(std::vector<Client>& clients, std::vector<char>& name){
  for (int i = 0;i<clients.size();i++){
    if (clients[i].name == name){
      clients.erase(clients.begin()+i);
    }
  }
}




void AddNewConnection(int socket, std::vector<Client>& clients){
//  int connection = fcntl(socket, F_GETFD, O_NONBLOCK);
  int connection = accept(socket, NULL, NULL);
  if (connection > 0){
    std::vector<char> name = Read(connection);
    DeleteOldConnection(clients, name);
    Client client;
    client.name = name;
    client.connection = connection;
    clients.push_back(client);
  }
}


//void Send(std::vector<char>& message, std::vector<Client>& clients);



int main(){
  using namespace std::chrono_literals;
  struct sockaddr_in local;


  local.sin_family = AF_INET;
  local.sin_port = htons(8888);
  local.sin_addr.s_addr = htonl(INADDR_ANY);

  int sock = socket( AF_INET, SOCK_STREAM, 0);
  if (sock < 0){
    perror("socket error");
    return 1;
  }
  int opt = 1;

  if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof (opt)) == -1)
    perror("setsockopt");


  int rc = bind(sock, (struct sockaddr*)&local, sizeof(local));
  if (rc<0){
    perror("error bind");
    return 1;
  }
  
  rc = listen(sock, 5);
  if (rc){
    perror("listen error");
    return 1;
  }
  fcntl(sock, F_SETFL, O_NONBLOCK);



  std::vector<Client> clients;
//  std::vector<std::vector<char>> messages;
  while (true)
  {
    std::this_thread::sleep_for(100ms);
    AddNewConnection(sock, clients);
    for (Client client : clients){
      std::vector<char> message = Read(client.connection);
      if (!message.empty()){
        int user_who_send = WhomSend(message, clients);
        PreparationForSending(message);
        Send(user_who_send, message);
      }
      // if (!message.empty()){
      //   Send(message, clients);
      // }
    }

  }
}
*/

#include "server.h"
#include <thread>
#include <chrono>
#include <poll.h>

int main(){
  using namespace std::chrono_literals;
  Server server;
  while (true){
    std::this_thread::sleep_for(100ms);
    server.Next();
  }
}