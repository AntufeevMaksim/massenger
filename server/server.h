#ifndef SERVER_H
#define SERVER_H


#include "client.h"
#include "connection.h"


class Server
{
private:
  Connection connection;
  std::vector<Client> clients;
  void AddNewConnection();
  std::vector<std::string> GetMessages(const std::string& message);
  bool IsMessageDelemiter(int i, const std::string& str);
  void SendSavedMessages(int sock, std::string& name);
  void UsernameChangedMessage(std::string& old_name, std::string& new_name);
public:
  Server();
  void Next();
  void Send(int sock, std::string& message);
  void SetUserName(int sock, std::string& name);
  std::vector<std::string> GetOnlineUsersNames();
  void BrokeConnection(int sock);
  Client FindUser(std::string& name);
};

#endif // SERVER_H

