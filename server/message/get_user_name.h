#ifndef GET_USER_NAME_H
#define GET_USER_NAME_H

#include "message.h"

class GetUserName : public Message{
  std::string _answer;

  public:
    GetUserName(std::string message, int sock, Server *server);
    void Send();
};

#endif