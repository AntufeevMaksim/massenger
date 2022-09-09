#ifndef BROKE_CONNECTION_H
#define BROKE_CONNECTION_H

#include "message.h"

class BrokeConnection : public Message{
  void Parse();

  public:
    BrokeConnection(std::string message, int sock, Server *server);
    void Send();
};




#endif