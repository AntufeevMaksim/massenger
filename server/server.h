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
  void SendSavedMessages(int sock, int user_id);
public:
  Server();
  void Next();
  void Send(int sock, std::string& message);
  void ChangeUserName(int sock, std::string& name);
  std::vector<int> GetOnlineUsersId();
  void BrokeConnection(int sock);
  Client FindUser(int user_id);
  void InitializeUser(int sock, int user_id);
};

#endif // SERVER_H

