#ifndef BROKE_CONNECTION_H
#define BROKE_CONNECTION_H

#include "message.h"

class BrokeConnection : public Message{
  std::string _username;
  void Parse();

  public:
    BrokeConnection(std::string message, int sock, Server *server);
    void Send();
};




#endif