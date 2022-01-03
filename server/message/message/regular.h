#ifndef REGULAR_H
#define REGULAR_H

#include "message.h"

class Regular : public Message{
  std::string _text;
  std::string _who_send;
  std::string _whom_send;
  void Parse(std::string& message);
  std::string Formation();
  public:
    Regular(std::string message, int who_send_sock, Server *server);
    void Send();

};

#endif //REGULAR_H