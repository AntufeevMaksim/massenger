#include "userdata.h"

#include "serverinterface.h"

#include <rapidjson/document.h>
#include <rapidjson/istreamwrapper.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/ostreamwrapper.h>
#include <rapidjson/filewritestream.h>
#include "rapidjson/filereadstream.h"
#include <rapidjson/prettywriter.h>

#include <cstdio>
#include <cstring>
#include <fstream>

int UserData::LoadUserId(){
    using namespace rapidjson;
    std::ifstream ifs { R"(userdata.json)" };

    IStreamWrapper isw { ifs };

    Document doc {};
    doc.ParseStream( isw );

    StringBuffer buffer {};
    Writer<StringBuffer> writer { buffer };
    doc.Accept( writer );


    Value& Id = doc["id"];
    int userId = Id.GetInt();
    ifs.close();
    return userId;
}


void UserData::SaveUserId(int user_id){
    using namespace rapidjson;

    Document doc;
    std::ifstream ifs { R"(userdata.json)" };

    IStreamWrapper isw { ifs };

    doc.ParseStream( isw );
    ifs.close();


    Value id;
    id.SetInt(user_id);
    doc["id"] = id;

    FILE* fp = fopen("userdata.json", "w");

    char buffer[1024];
    FileWriteStream os(fp, buffer, sizeof(buffer));

    Writer<FileWriteStream> writer(os);
    doc.Accept(writer);

    fclose(fp);
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



void UserData::LoadListFriends(QListWidget& users, ServerInterface *server){
    using namespace rapidjson;
    std::ifstream ifs { R"(userdata.json)" };

    IStreamWrapper isw { ifs };

    Document doc {};
    doc.ParseStream( isw );

    StringBuffer buffer {};
    Writer<StringBuffer> writer { buffer };
    doc.Accept( writer );

    Value& friends = doc["my_friends"];

    int id;
    for (SizeType i = 0; i < friends.Size(); i++){
        QListWidgetItem *user = new QListWidgetItem();
        id = friends[i]["id"].GetInt();
        user->setData(Qt::UserRole, id);
        user->setText(server->GetUserName(id));
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

    QVariant data = user.data(Qt::UserRole);
    int user_id = data.toInt();
    for (SizeType i = 0; i < friends.Size(); i++){
        if(user_id == friends[i]["id"].GetInt()){
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


void UserData::AddNewFriend(QListWidgetItem* new_friend){
    using namespace rapidjson;

    Document doc;
    std::ifstream ifs { R"(userdata.json)" };

    IStreamWrapper isw { ifs };

    doc.ParseStream( isw );
    ifs.close();

    Value new_user(rapidjson::kObjectType);

    Value name;
    name.SetString(new_friend->text().toStdString().c_str(), new_friend->text().size());
    new_user.AddMember("name", name, doc.GetAllocator());

    Value id;
    QVariant data = new_friend->data(Qt::UserRole);
    int user_id = data.toInt();
    id.SetInt(user_id);
    new_user.AddMember("id", id, doc.GetAllocator());

    Value chat_history;
    chat_history.SetArray();
    new_user.AddMember("chat_history", chat_history, doc.GetAllocator());

    doc["my_friends"].PushBack(new_user, doc.GetAllocator());

    FILE* fp = fopen("userdata.json", "w");

    char buffer[1024];
    FileWriteStream os(fp, buffer, sizeof(buffer));

    Writer<FileWriteStream> writer(os);
    doc.Accept(writer);

    fclose(fp);
}


void UserData::AddNewMessage(int id, QString string_message, UserType& user_type){
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

    Value& users = doc["my_friends"];
    Value message;
    message.SetString(ready_message.c_str(), ready_message.size());

    for (SizeType i = 0; i < users.Size(); i++){
      if(users[i]["id"].GetInt() == id){
        users[i]["chat_history"].PushBack(message, doc.GetAllocator());
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

void UserData::LoadChatHistory(QListWidget *chat, int id){

    using namespace rapidjson;
    Document doc;
    std::ifstream ifs { R"(userdata.json)" };

    IStreamWrapper isw { ifs };

    doc.ParseStream( isw );
    ifs.close();

    Value& users = doc["my_friends"];

    for (SizeType i = 0; i < users.Size(); i++){
        if(users[i]["id"].GetInt() == id){
            for (SizeType i2 = 0; i2 < users[i]["chat_history"].Size(); i2++){
                QListWidgetItem *message = new QListWidgetItem;
                QString text = users[i]["chat_history"][i2].GetString();
                text.remove(0,1);
                message->setText(text.toStdString().c_str());
                if(users[i]["chat_history"][i2].GetString()[0] == 'u'){
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
