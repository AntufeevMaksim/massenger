#ifndef INITIALIZE_USER_H
#define INITIALIZE_USER_H

#include "message.h"

class InitializeUser : public Message{
  int _user_id;
  void Parse(std::string& message);
  public:
    InitializeUser(std::string message, int sock, Server *server);
    void Send();
};

#endif