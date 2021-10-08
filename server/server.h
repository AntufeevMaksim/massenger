#ifndef SERVER_H
#define SERVER_H


#include "client.h"
#include "connection.h"
#include "message.h"
class Server
{
private:
  Connection connection;
  std::vector<Client> clients;
  void AddNewConnection();
  void Send(Message& message);
  Client FindUser(std::string& name);
//  Message ParseMessage(std::vector<char>& message, int who_send_sock);
//  Message ParseRegularMessage(std::vector<char>& message);
  std::vector<Message> GetMessages(std::string& str_message, int who_send_sock);
  std::vector<char> MessageFormation(Message& message);
  void BrokeOldConnection(int sock);
  void SetUserName(Message& message);
  bool IsActiveUser(std::string& user);
  bool IsMessageDelemiter(int i, std::string& str);
public:
  Server();
  void Next();
};

#endif // SERVER_H