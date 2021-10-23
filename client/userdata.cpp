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
void UserData::LoadListFriends(QListWidget& users){
    std::string name;
    std::fstream file("my_friends");
    while(getline(file, name)){
        if (!name.empty()){
            QListWidgetItem *user = new QListWidgetItem();
            user->setText(name.c_str());
            users.addItem(user);
        }
    }
    file.close();
}

void UserData::DeleteFriend(QListWidget &users, QListWidgetItem &user){
    std::string name;
    std::vector<std::string> friends;
    std::fstream file("my_friends", file.out);
    for (int i = 0; i < users.count(); i++) {
        friends.push_back(users.item(i)->text().toStdString());
    }
    auto i = std::remove(friends.begin(), friends.end(), user.text().toStdString());
    friends.erase(i, friends.end());

    for(std::string name : friends){
        file << name + "\n";
    }
    file.close();
    delete users.takeItem(users.row(&user));
}

QString UserData::LoadUsername(){
/*    using namespace rapidjson;

    std::ifstream ifs { R"(userdata.json)" };

    IStreamWrapper isw { ifs };

    Document doc {};
    doc.ParseStream( isw );

    StringBuffer buffer {};
    Writer<StringBuffer> writer { buffer };
    doc.Accept( writer );

    Value& name = doc["username"];
    QString username = name.GetString();
    return username;
*/
    using namespace rapidjson;
    std::ifstream ifs { R"(userdata.json)" };

    IStreamWrapper isw { ifs };

    Document doc {};
    doc.ParseStream( isw );

    StringBuffer buffer {};
    Writer<StringBuffer> writer { buffer };
    doc.Accept( writer );

    bool b = doc.IsObject();

    Value& name = doc["username"];
    QString username = name.GetString();
    ifs.close();
    return username;
}

void UserData::SetUsername(QString &username){
    using namespace rapidjson;
/*
//    std::ifstream ifs { R"(userdata.json)" };
    std::ofstream ifs("userdata.json");
    OStreamWrapper osw(ifs);

    Document doc;
//    doc.ParseStream( isw );

//    StringBuffer buffer {};
    Writer<OStreamWrapper> writer(osw);
    doc.Accept( writer );

    Value& name = doc["username"];
//    QString username = name.GetString();
*/
/*
    Document d;
    d.Parse("");
    ofstream ofs("userdata.json");
    OStreamWrapper osw(ofs);

    Writer<OStreamWrapper> writer(osw);
    d.Accept(writer);
*/
//    Document d;
//    d.Parse(json);
    // ...
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





/*
    Document d;

    std::ofstream ofs("userdata.json");
    OStreamWrapper osw(ofs);

    Writer<OStreamWrapper> writer(osw);
    d.Accept(writer);

//    Value& name = d["username"];
    Type t = d.GetType();
    Value& v = d[0];
//    name.SetString(username.toStdString().c_str(), username.size());
    ofs.close();
*/
}





