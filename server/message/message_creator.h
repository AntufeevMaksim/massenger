#ifndef MESSAGE_CREATOR_H
#define MESSAGE_CREATOR_H

#include <vector>
#include <string>
#include "server.h"
#include <memory>
#include "client.h"
class MessageCreator
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
