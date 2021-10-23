#ifndef MESSAGE_H
#define MESSAGE_H

#include <vector>
#include <string>
class Message
{
  public:
    enum TypeMessage{
    REGULAR,
    GET_ALL_USERS,
    CLIENT_NAME,
    BROKE_CONNECTION,
    GET_USERS_STATUS,
    SET_USER_NAME
    };

    Message(std::string message, int who_send_sock);
    TypeMessage GetType();
    std::string GetText();
    std::string  GetWhoSend();
    std::string  GetWhomSend();
    int GetWhoSendSock();
    std::string  Formation();
  private:
    void ParseRegularMessage(std::string& message);

    int _who_send_sock;
    std::string _text;
    std::string _who_send;
    std::string _whom_send;
    TypeMessage _type;

};

#endif // CLIENT_H

