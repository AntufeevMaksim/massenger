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
#include <QString>

class Server
{
public:
    Server();
    void SendMessage(QString& message);
    QString ReadMessage();

private:
    int sock;
    int number_message;
    int Connect();
};

#endif // SERVER_H
