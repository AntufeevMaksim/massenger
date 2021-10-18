#include "message.h"

Message::Message(std::string message, int who_send_sock){
   _who_send_sock = who_send_sock;
  switch (message[0])
  {
  case 'r':
    message.erase(message.begin());
    ParseRegularMessage(message);
    _type = REGULAR;
    break;
  
  case 'g':
    _type = GET_ALL_USERS;
    break;

  case 'b':
    _type = BROKE_CONNECTION;
    break;

  case 's':
    _type = GET_USERS_STATUS;
    message.erase(message.begin());
    _text = message;
    break;

  case 'n':
    _type = SET_USER_NAME;
    message.erase(message.begin());
    _text = message;
    break;
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

void Message::ParseRegularMessage(std::string& message){
  int i = 0;
  std::string buf;
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

std::string Message::Formation(){
  std::string ready_message;
  if (_type == Message::REGULAR){
    ready_message += 'r';
    ready_message += _who_send;
    ready_message.push_back('|');
    for (char c : _text){
      ready_message.push_back(c);
    }
    ready_message += "#?#";
  }
  return ready_message;  
}

std::string Message::GetText(){
  return _text;
}
Message::TypeMessage Message::GetType(){
  return _type;
}

std::string Message::GetWhomSend(){
  return _whom_send;
}

std::string Message::GetWhoSend(){
  return _who_send;
}

int Message::GetWhoSendSock(){
  return _who_send_sock;
}