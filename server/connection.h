#ifndef CONNECTION_H
#define CONNECTION_H

#include <vector>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <stdio.h>

class Connection
{
private:
  int _sock;
  void Connect();
public:
  struct sockaddr_in local;
  Connection();
  void Send(int s, std::vector<char>& message);
  void Send(int s, std::string& buf);
  std::string Read(int s);
  int accept_new_connection();
};

#endif // CONNECTION_H