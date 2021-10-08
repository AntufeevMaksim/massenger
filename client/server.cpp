#include "server.h"
#include "stdio.h"
#include <thread>
#include <chrono>
#include <poll.h>
Server::Server()
{
    number_message = 0;
    sock = Connect();
}


int Server::Connect(){
    sock = -1;
    struct sockaddr_in local;
    local.sin_family = AF_INET;
    local.sin_port = htons(8888);
    local.sin_addr.s_addr = inet_addr("127.0.0.1");

    sock = socket( AF_INET, SOCK_STREAM, 0);
    if (sock < 0){
      perror("socket error");
    }

    int rc = connect(sock, (struct sockaddr*)&local, sizeof(local));
    if (rc){
      perror("error connect");
    }
    return sock;
}


std::vector<char> Server::ReadMessage(){
    fd_set readfs;
    FD_ZERO(&readfs);
    FD_SET(sock, &readfs);

    struct timeval tv;
    tv.tv_sec = 0;
    tv.tv_usec = 100;

    int n;

    int res = select(sock+1, &readfs, NULL, NULL, &tv);
  //  int rc = recv(s, buf.data(), 3, 0);
    if (res>0){
      ioctl(sock, TIOCINQ, &n);
      std::vector<char> buf(n);
      int rc = recv(sock, buf.data(), n, 0);
      return (rc == 0 ? std::vector<char>{} : buf);
    }
    else{
      return {};
    }
}


void Server::SendMessage(std::string& message){
    if (sock < 0){
        perror("sock < 0");
    }
    message += "#?#";
    int rc = send(sock, message.data(), message.size(), 0);
    if (rc <= 0){
      perror("error send");
    }
}


