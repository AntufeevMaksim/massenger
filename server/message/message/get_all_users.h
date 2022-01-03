#ifndef GET_ALL_USERS_H
#define GET_ALL_USERS_H

#include "message.h"

class GetAllUsers : public Message{
  std::string _all_users;
  public:
    GetAllUsers(std::string message, int sock, Server *server);
    void Send();

};




#endif