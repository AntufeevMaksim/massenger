#ifndef MESSAGE_H
#define MESSAGE_H

#include <vector>

class Message
{
  public:
    enum TypeMessage{
    REGULAR,
    GET_ALL_USERS,
    CLIENT_NAME,
    BROKE_CONNECTION,
    GET_USERS_STATUS
    };

    Message(std::vector<char> message, int who_send_sock);
    TypeMessage GetType();
    std::vector<char> GetText();
    std::vector<char> GetWhoSend();
    std::vector<char> GetWhomSend();
    int GetWhoSendSock();
    std::vector<char> Formation();
  private:
    void ParseRegularMessage(std::vector<char>& message);

    int _who_send_sock;
    std::vector<char> _text;
    std::vector<char> _who_send;
    std::vector<char> _whom_send;
    TypeMessage _type;

};

#endif // CLIENT_H