#include "message.h"

Message::Message(std::vector<char> message, int who_send_sock){
   _who_send_sock = who_send_sock;
  switch (message[0])
  {
  case 'r':
    message.erase(message.begin());
    ParseRegularMessage(message);
    _type = Message::REGULAR;
    break;
  
  case 'g':
    _type = Message::GET_ALL_USERS;
    break;

  case 'b':
    _type = Message::BROKE_CONNECTION;
    break;

  case 's':
    _type = Message::GET_USERS_STATUS;
    message.erase(message.begin());
    _text = message;
  default:
    break;
  }
/*
  if (message[0] == 'r'){
    message.erase(message.begin());
    ParseRegularMessage(message);
    _type = Message::REGULAR;
  }
  if (message[0] == 'g' ){
    _type = Message::GET_ALL_USERS;
  }
  if (message[0] == 'b'){
    _type = Message::BROKE_CONNECTION;
  }
*/

}

void Message::ParseRegularMessage(std::vector<char>& message){
  int i = 0;
  std::vector<char> buf;
  for (char c : message){
    if (c == '|'){
      if (_whom_send.empty()){
        _whom_send = buf;
        buf.clear();
      }
      else if (_who_send.empty()){
        _who_send = buf;
        buf.clear();
      }
    }
    else{
      buf.push_back(c);
    }
    i++;
  }
  _text = buf;
}

std::vector<char> Message::Formation(){
  std::vector<char> ready_message;
  if (_type == Message::REGULAR){
    ready_message = _who_send;
    ready_message.push_back('|');
    for (char c : _text){
      ready_message.push_back(c);
    }
  }
  return ready_message;  
}

std::vector<char> Message::GetText(){
  return _text;
}
Message::TypeMessage Message::GetType(){
  return _type;
}

std::vector<char> Message::GetWhomSend(){
  return _whom_send;
}

std::vector<char> Message::GetWhoSend(){
  return _who_send;
}

int Message::GetWhoSendSock(){
  return _who_send_sock;
}