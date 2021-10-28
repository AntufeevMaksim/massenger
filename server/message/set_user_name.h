#ifndef SET_USER_NAME_H
#define SET_USER_NAME_H

#include "message.h"

class SetUserName : public Message{
  std::string _user_name;
  void Parse(std::string& message);
  public:
    SetUserName(std::string message, int sock, Server *server);
    void Send();
  
};

#endif