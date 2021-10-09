#ifndef SERVERINTERFACE_H
#define SERVERINTERFACE_H
#include <QString>
#include <vector>
#include "string"


#include <thread>
#include <chrono>
#include <poll.h>
#include <server.h>
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
    ServerInterface(QString user_name);
//    ~ServerInterface();
    void SendMessage(QString& message, QString& friend_name, QString& user_name);
    QString ReadMessage(QString& friend_name);
    std::vector<QString> GetAllUsers();
    void BreakConnection();
    QString GetUsersStatus(QString& users);

private:
    std::string user_name;
//    std::vector<Client> clients;
    Server server;
    QString Get_system_info(QString& friend_name, QString& user_name);
    QString GetWhoSend(QString& message);
    void DeleteSystemInfo(QString& message);
//    void AddNewMessage(std::vector<char>& who_send, std::vector<char>& message);
};

std::vector<std::string> _GetAllUsers();



#endif // SERVERINTERFACE_H
