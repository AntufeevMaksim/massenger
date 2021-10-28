#ifndef SERVER_H
#define SERVER_H


#include "client.h"
#include "connection.h"
//#include "message/message.hpp"
#include "memory"

class Server
{
private:
  Connection connection;
  std::vector<Client> clients;
  void AddNewConnection();
//  void Send(Message& message);
  std::vector<std::string> GetMessages(const std::string& message);
//  Message ParseMessage(std::vector<char>& message, int who_send_sock);
//  Message ParseRegularMessage(std::vector<char>& message);
//  std::vector<std::unique_ptr<Message>> GetMessages(std::string& str_message, int who_send_sock);
//  std::vector<char> MessageFormation(Message& message);
//  void BrokeOldConnection(int sock);
//  void SetUserName(Message& message);
//  bool IsActiveUser(std::string& user);
  bool IsMessageDelemiter(int i, const std::string& str);
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

