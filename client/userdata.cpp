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
        user->setText(friends[i].GetString());
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
        if(!std::strcmp(friends[i].GetString(), user.text().toStdString().c_str())){
            friends.Erase(friends.Begin() + i);
        }
    }

    FILE* fp = fopen("userdata.json", "w"); // non-Windows use "w"

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

    FILE* fp = fopen("userdata.json", "w"); // non-Windows use "w"

    char buffer[1024];
    FileWriteStream os(fp, buffer, sizeof(buffer));

    Writer<FileWriteStream> writer(os);
    doc.Accept(writer);

    fclose(fp);

}


void UserData::AddNewFriend(QString &name){
    using namespace rapidjson;

    Document doc;
    std::ifstream ifs { R"(userdata.json)" };

    IStreamWrapper isw { ifs };

    doc.ParseStream( isw );
    ifs.close();

    Value friend_name;
    friend_name.SetString(name.toStdString().c_str(), name.size());

    doc["my_friends"].PushBack(friend_name, doc.GetAllocator());

    FILE* fp = fopen("userdata.json", "w"); // non-Windows use "w"

    char buffer[1024];
    FileWriteStream os(fp, buffer, sizeof(buffer));

    Writer<FileWriteStream> writer(os);
    doc.Accept(writer);

    fclose(fp);
}


void UserData::AddNewMessage(QString &username, QString &string_message){
    using namespace rapidjson;
    Document doc;
    std::ifstream ifs { R"(userdata.json)" };

    IStreamWrapper isw { ifs };

    doc.ParseStream( isw );
    ifs.close();

    Value message;
    message.SetString(string_message.toStdString().c_str(), string_message.size());

    doc["my_friends"][username.toStdString().c_str()].PushBack(message, doc.GetAllocator());

    FILE* fp = fopen("userdata.json", "w"); // non-Windows use "w"

    char buffer[1024];
    FileWriteStream os(fp, buffer, sizeof(buffer));

    Writer<FileWriteStream> writer(os);
    doc.Accept(writer);

    fclose(fp);
}

























