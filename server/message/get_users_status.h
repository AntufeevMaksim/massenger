#ifndef GET_USERS_STATUS_H
#define GET_USERS_STATUS_H

#include "message.h"

class GetUsersStatus : public Message{
  std::vector<int> _users_id;
  void Parse(std::string& message);
  public:
    GetUsersStatus(std::string message, int sock, Server *server);
    void Send();
};




#endif