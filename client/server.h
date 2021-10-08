#ifndef SERVER_H
#define SERVER_H

#include <string>
#include <vector>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <stdio.h>

class Server
{
public:
    Server();
    void SendMessage(std::string& message);
    std::vector<char> ReadMessage();

private:
    int sock;
    int number_message;
    int Connect();
};

#endif // SERVER_H
