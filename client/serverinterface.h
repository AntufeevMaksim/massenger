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
    ServerInterface(int user_id);
    void SendMessage(QString& message, int friend_id, int user_id);
    QString ReadMessage(int friend_id, Message::TypeMessage type_message);
    std::vector<QString> GetAllUsers();
    void BreakConnection();
    QString GetUsersStatus(QString& users);
    void SendUsername(QString username);
    void SendUserId(int user_id);
    int GetUserId();
    QString GetUserName(int id);

private:
    std::vector<Message> _messages;
    std::string user_name;
    Server server;
    QString Get_system_info(int friend_id, int user_id);
    QString GetWhoSend(QString& message);
    void DeleteSystemInfo(QString& message);
    void ParseMessage(QString& message);
    bool IsMessageDelemiter(int i, QString& str);
};

std::vector<std::string> _GetAllUsers();



#endif // SERVERINTERFACE_H
