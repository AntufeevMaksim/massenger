#include "userdata.h"
#include <fstream>
#include <rapidjson/document.h>
#include <rapidjson/istreamwrapper.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/ostreamwrapper.h>
#include <rapidjson/filewritestream.h>
#include "rapidjson/filereadstream.h"
#include <cstdio>
#include <rapidjson/prettywriter.h>
#include <cstring>

void UserData::LoadListFriends(QListWidget& users){
    using namespace rapidjson;
    std::ifstream ifs { R"(userdata.json)" };

    IStreamWrapper isw { ifs };

    Document doc {};
    doc.ParseStream( isw );

    StringBuffer buffer {};
    Writer<StringBuffer> writer { buffer };
    doc.Accept( writer );

    Value& friends = doc["my_friends"];


    for (SizeType i = 0; i < friends.Size(); i++){
        QListWidgetItem *user = new QListWidgetItem();
        user->setText(friends[i][0].GetString());
        users.addItem(user);
    }
    ifs.close();
}

void UserData::DeleteFriend(QListWidget &users, QListWidgetItem &user){
    using namespace rapidjson;

    Document doc;
    std::ifstream ifs { R"(userdata.json)" };

    IStreamWrapper isw { ifs };

    doc.ParseStream( isw );
    ifs.close();

    Value& friends = doc["my_friends"];

    for (SizeType i = 0; i < friends.Size(); i++){
        if(!std::strcmp(friends[i][0].GetString(), user.text().toStdString().c_str())){
            friends.Erase(friends.Begin() + i);
        }
    }

    FILE* fp = fopen("userdata.json", "w");

    char buffer[1024];
    FileWriteStream os(fp, buffer, sizeof(buffer));

    Writer<FileWriteStream> writer(os);
    doc.Accept(writer);

    fclose(fp);

    delete users.takeItem(users.row(&user));
}

QString UserData::LoadUsername(){

    using namespace rapidjson;
    std::ifstream ifs { R"(userdata.json)" };

    IStreamWrapper isw { ifs };

    Document doc {};
    doc.ParseStream( isw );

    StringBuffer buffer {};
    Writer<StringBuffer> writer { buffer };
    doc.Accept( writer );


    Value& name = doc["username"];
    QString username = name.GetString();
    ifs.close();
    return username;
}

void UserData::SetUsername(QString &username){
    using namespace rapidjson;

    Document doc;
    std::ifstream ifs { R"(userdata.json)" };

    IStreamWrapper isw { ifs };

    doc.ParseStream( isw );
    ifs.close();

    doc["username"].SetString(username.toStdString().c_str(), username.size());

    FILE* fp = fopen("userdata.json", "w");

    char buffer[1024];
    FileWriteStream os(fp, buffer, sizeof(buffer));

    Writer<FileWriteStream> writer(os);
    doc.Accept(writer);

    fclose(fp);

}


void UserData::AddNewFriend(QString &str_name){
    using namespace rapidjson;

    Document doc;
    std::ifstream ifs { R"(userdata.json)" };

    IStreamWrapper isw { ifs };

    doc.ParseStream( isw );
    ifs.close();

    Value friend_;
    friend_.SetArray();
    Value name;
    name.SetString(str_name.toStdString().c_str(), str_name.size());
    friend_.PushBack(name, doc.GetAllocator());

    doc["my_friends"].PushBack(friend_, doc.GetAllocator());

    FILE* fp = fopen("userdata.json", "w");

    char buffer[1024];
    FileWriteStream os(fp, buffer, sizeof(buffer));

    Writer<FileWriteStream> writer(os);
    doc.Accept(writer);

    fclose(fp);
}


void UserData::AddNewMessage(QString &username, QString string_message, UserType& user_type){
    using namespace rapidjson;
    Document doc;
    std::ifstream ifs { R"(userdata.json)" };

    IStreamWrapper isw { ifs };

    doc.ParseStream( isw );
    ifs.close();

    std::string ready_message(string_message.toStdString().c_str());

    if(user_type == this_user)
        ready_message = "u" + ready_message;
    else{
        ready_message = "f" + ready_message;
    }

    std::string _whom_send(username.toStdString().c_str());

    Value& users = doc["my_friends"];
    Value message;
    message.SetString(ready_message.c_str(), ready_message.size());

    for (SizeType i = 0; i < users.Size(); i++){
      if(!std::strcmp(users[i][0].GetString(), _whom_send.c_str())){
        users[i].PushBack(message, doc.GetAllocator());
        break;
      }
    }

    FILE* fp = fopen("userdata.json", "w");

    char buffer[1024];
    FileWriteStream os(fp, buffer, sizeof(buffer));

    Writer<FileWriteStream> writer(os);
    doc.Accept(writer);

    fclose(fp);
}

void UserData::LoadChatHistory(QListWidget *chat, QString &username){

    using namespace rapidjson;
    Document doc;
    std::ifstream ifs { R"(userdata.json)" };

    IStreamWrapper isw { ifs };

    doc.ParseStream( isw );
    ifs.close();

    Value& users = doc["my_friends"];

    for (SizeType i = 0; i < users.Size(); i++){
        if(!std::strcmp(users[i][0].GetString(), username.toStdString().c_str())){
            for (SizeType i2 = 1; i2 < users[i].Size(); i2++){
                QListWidgetItem *message = new QListWidgetItem;
                QString text = users[i][i2].GetString();
                text.remove(0,1);
                message->setText(text.toStdString().c_str());
                if(users[i][i2].GetString()[0] == 'u'){
                    message->setBackground(Qt::green);
                }
                chat->addItem(message);
            }
        }
    }


    FILE* fp = fopen("userdata.json", "w");

    char buffer[1024];
    FileWriteStream os(fp, buffer, sizeof(buffer));

    Writer<FileWriteStream> writer(os);
    doc.Accept(writer);

    fclose(fp);
}
