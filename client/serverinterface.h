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
#include <message.h>


class ServerInterface
{

public:
    ServerInterface();
    ServerInterface(QString user_name);
    void SendMessage(QString& message, QString& friend_name, QString& user_name);
    QString ReadMessage(QString& friend_name, Message::TypeMessage type_message);
    std::vector<QString> GetAllUsers();
    void BreakConnection();
    QString GetUsersStatus(QString& users);
    void SendUsername(QString username);

private:
    std::vector<Message> _messages;
    std::string user_name;
    Server server;
    QString Get_system_info(QString& friend_name, QString& user_name);
    QString GetWhoSend(QString& message);
    void DeleteSystemInfo(QString& message);
    void ParseMessage(QString& message);
    bool IsMessageDelemiter(int i, QString& str);
};

std::vector<std::string> _GetAllUsers();



#endif // SERVERINTERFACE_H
