#ifndef SERVERINTERFACE_H
#define SERVERINTERFACE_H
#include <QString>
#include <vector>
#include "string"

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <thread>
#include <chrono>
#include <poll.h>
#include <sys/ioctl.h>
#include <QTimer>
#include <QObject>



/*
struct Client
{
private:
    std::vector<char> _name;
    std::vector<char> _message;

public:
    Client(std::vector<char>& name, std::vector<char>& message);
    std::vector<char> GetName();
    std::vector<char> GetMessage();
    void ClearMessage();
    void AddMessage(std::vector<char>& message);
};
*/



class ServerInterface
{

public:
    ServerInterface();
    ServerInterface(QString& user_name);
    void SendMessage(QString& message, QString& friend_name, QString& user_name);
    QString ReadMessage(QString& friend_name);
    std::vector<std::string> GetAllUsers();

private:
    int sock;
    struct sockaddr_in local;
    std::string user_name;
//    std::vector<Client> clients;

    std::string Get_system_info(QString& friend_name, QString& user_name);
    int Connect_to_server();
    std::vector<char> Read(int sock);
    std::vector<char> GetWhoSend(std::vector<char>& message);
    void DeleteSystemInfo(std::vector<char>& message);
//    void AddNewMessage(std::vector<char>& who_send, std::vector<char>& message);
    //QTimer timer_message_check;
};

std::vector<std::string> _GetAllUsers();



#endif // SERVERINTERFACE_H
