#ifndef MESSAGE_H
#define MESSAGE_H

#include <vector>
#include <string>
#include "server.h"
#include <memory>
#include "client.h"
class Message
{
  public:
    static Message* New(std::string message, int who_send_sock, Server *server);
    virtual ~Message();
    virtual void Send();
  protected:
    int _who_send_sock;
    Server *_server;
};

#endif // CLIENT_H