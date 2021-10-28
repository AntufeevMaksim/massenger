#ifndef GET_USERS_STATUS_H
#define GET_USERS_STATUS_H

#include "message.h"

class GetUsersStatus : public Message{
  std::vector<std::string> _users_names;
  void Parse(std::string& message);
  public:
    GetUsersStatus(std::string message, int sock, Server *server);
    void Send();
};




#endif