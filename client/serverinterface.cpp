#include "serverinterface.h"

/*
Client::Client(std::vector<char>& name, std::vector<char>& message){
    _message = message;
    _name = name;
}

std::vector<char> Client::GetName(){
    return _name;
}

std::vector<char> Client::GetMessage(){
    return _message;
}

void Client::ClearMessage(){
    _message.clear();
}

void Client::AddMessage(std::vector<char>& message){
    _message.push_back('/n');
    for (char c : message){
        _message.push_back(c);
    }
}
*/





int ServerInterface::Connect_to_server(){
    local.sin_family = AF_INET;
    local.sin_port = htons(8888);
    local.sin_addr.s_addr = inet_addr("127.0.0.1");

    sock = socket( AF_INET, SOCK_STREAM, 0);
    if (sock < 0){
      perror("socket error");
    }

    int rc = connect(sock, (struct sockaddr*)&local, sizeof(local));
    if (rc){
      perror("error connect");
    }
    return sock;
}

ServerInterface::ServerInterface(QString& user_name){

    sock = Connect_to_server();
    std::string std_user_name = user_name.toStdString();
    send(sock, std_user_name.c_str(), std_user_name.size(), 0);


}




std::string ServerInterface::Get_system_info(QString& friend_name, QString& user_name)
{
    std::string system_info;
    system_info += user_name.toStdString();
    system_info += "|";
    system_info += friend_name.toStdString();
    system_info += "|";

    return system_info;
}

void ServerInterface::SendMessage(QString& message, QString& friend_name, QString& user_name){
    std::string std_message = Get_system_info(friend_name, user_name);

    std_message += message.toStdString();

    send(sock, std_message.c_str(), std_message.size(), 0);

}

std::vector<char> ServerInterface::Read(int s){
  fd_set readfs;
  FD_ZERO(&readfs);
  FD_SET(s, &readfs);

  struct timeval tv;
  tv.tv_sec = 0;
  tv.tv_usec = 100;

  int n;

  int res = select(s+1, &readfs, NULL, NULL, &tv);
//  int rc = recv(s, buf.data(), 3, 0);
  if (res>0){
    ioctl(s, TIOCINQ, &n);
    std::vector<char> buf(n);
    int rc = recv(s, buf.data(), n, 0);
    printf("%s", buf.data());
    return (rc == 0 ? std::vector<char>{} : buf);
  }
  else{
    return {};
  }
}


std::vector<char> ServerInterface::GetWhoSend(std::vector<char>& message){
    std::vector<char> who_send;
    for (char c : message){
        if (c == '|'){
            return who_send;
        }
        who_send.push_back(c);
    }
}

void ServerInterface::DeleteSystemInfo(std::vector<char>& message){
    int i = 0;
      for (char c : message){
        if (c == '|'){
          message.erase(message.begin(), message.begin() + i+1);
          break;
        }
      i++;
      }
}

/*
void ServerInterface::AddNewMessage(std::vector<char>& who_send, std::vector<char>& message){
    for (Client client : clients){
        if (client.GetName() == who_send){
            client.AddMessage(message);
        }
    }

    Client client(who_send, message);
    clients.push_back(client);
}
*/




/*
void ServerInterface::ReadMessage(){
    std::vector<char> message = Read(sock);
    if (!message.empty()){
        std::vector<char> who_send = GetWhoSend(message);
        DeleteSystemInfo(message);
        AddNewMessage(who_send, message);
    }
}
*/



QString ServerInterface::ReadMessage(QString& friend_name){
    std::vector<char> message = Read(sock);
    if (!message.empty()){
        if (QString(GetWhoSend(message).data()) == friend_name){
            DeleteSystemInfo(message);
            return QString(message.data());
        }

    }
}




ServerInterface::ServerInterface(){}










std::vector<std::string> ServerInterface::GetAllUsers(){
    std::vector<std::string> all_users;

    all_users.push_back(std::string("Maksim"));
    all_users.push_back(std::string("Ne Maksim"));
    return all_users;

}











