#include "workwithdatafile.h"

#include <rapidjson/istreamwrapper.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/ostreamwrapper.h>
#include <rapidjson/filewritestream.h>
#include "rapidjson/filereadstream.h"

#include <fstream>
#include <cstring>
/*
void WorkWithDataFile::SetUserName(std::string& new_name, std::string& old_name){
    if (new_name == old_name){
      return;
    }

    using namespace rapidjson;
    Document doc;
    std::ifstream ifs { R"(data.json)" };

    IStreamWrapper isw { ifs };

    doc.ParseStream( isw );
    ifs.close();


    Value& users = doc["users"];
    Value name;
    name.SetString(new_name.c_str(), new_name.size());

    bool this_new_user = true;
    for (SizeType i = 0; i < users.Size(); i++){
      if (!std::strcmp(users[i]["name"].GetString(), old_name.c_str()) || !std::strcmp(users[i]["name"].GetString(), new_name.c_str())){
        users[i]["name"] = name;
        this_new_user = false;
        break;
      }
    }

    if(this_new_user){
      Value new_user = WorkWithDataFile::CreateNewUser(name, doc);
      users.PushBack(new_user, doc.GetAllocator());
    }

    
    FILE* fp = fopen("data.json", "w");

    char buffer[1024];
    FileWriteStream os(fp, buffer, sizeof(buffer));

    Writer<FileWriteStream> writer(os);
    doc.Accept(writer);

    fclose(fp);
    
   Save(doc);
}
*/
void WorkWithDataFile::ChangeUserName(int user_id, std::string& new_name){
  using namespace rapidjson;
  Document doc;
  std::ifstream ifs { R"(data.json)" };

  IStreamWrapper isw { ifs };

  doc.ParseStream( isw );
  ifs.close();

  Value& users = doc["users"];
  Value name;
  name.SetString(new_name.c_str(), new_name.size());

  for (SizeType i = 0; i < users.Size(); i++){
    if (users[i]["id"].GetInt() == user_id){
      users[i]["name"] = name;
      break;
    }
  }
    FILE* fp = fopen("data.json", "w");

    char buffer[1024];
    FileWriteStream os(fp, buffer, sizeof(buffer));

    Writer<FileWriteStream> writer(os);
    doc.Accept(writer);

    fclose(fp);
}


std::string WorkWithDataFile::GetAllUsers(){
    using namespace rapidjson;

    std::string all_users{"g"};

    Document doc;
    std::ifstream ifs { R"(data.json)" };

    IStreamWrapper isw { ifs };

    doc.ParseStream( isw );
    ifs.close();

    Value& users = doc["users"];
    for (SizeType i = 0; i < users.Size(); i++){
      all_users += std::to_string(users[i]["id"].GetInt());
      all_users += "~&~";
      all_users += users[i]["name"].GetString();
      all_users += "\n";
    }

    return all_users;

}


void WorkWithDataFile::SaveMessageForOfflineUser(int user_id, std::string& ready_message){

    using namespace rapidjson;
    Document doc;
    std::ifstream ifs { R"(data.json)" };

    IStreamWrapper isw { ifs };

    doc.ParseStream( isw );
    ifs.close();


    Value& users = doc["users"];
    Value message;
    message.SetString(ready_message.c_str(), ready_message.size());

    for (SizeType i = 0; i < users.Size(); i++){
      if(users[i]["id"].GetInt() == user_id){
        users[i]["messages_for_him"].PushBack(message, doc.GetAllocator());
        break;
      }
    }
    
    FILE* fp = fopen("data.json", "w");

    char buffer[1024];
    FileWriteStream os(fp, buffer, sizeof(buffer));

    Writer<FileWriteStream> writer(os);
    doc.Accept(writer);

    fclose(fp);
    
   //WorkWithDataFile::Save(doc);

}



std::vector<std::string> WorkWithDataFile::GetSavedMessages(int user_id){
    using namespace rapidjson;
    Document doc;
    std::ifstream ifs { R"(data.json)" };

    IStreamWrapper isw { ifs };

    doc.ParseStream( isw );
    ifs.close();

    Value& users = doc["users"];

    std::vector<std::string> saved_messages;

    for (SizeType i = 0; i < users.Size(); i++){
      if(user_id == users[i]["id"].GetInt()){
        for (size_t n = 0; n < users[i]["messages_for_him"].Size(); n++){
          saved_messages.push_back(std::string(users[i]["messages_for_him"][n].GetString()));
          users[i]["messages_for_him"].Erase(users[i]["messages_for_him"].Begin());
        }
        break;
      }
    }
  
   FILE* fp = fopen("data.json", "w");

    char buffer[1024];
    FileWriteStream os(fp, buffer, sizeof(buffer));

    Writer<FileWriteStream> writer(os);
    doc.Accept(writer);

    fclose(fp);
  
  //WorkWithDataFile::Save(doc);
  return saved_messages;

}

void WorkWithDataFile::CreateNewUser(int user_id){
  using namespace rapidjson;
  Document doc;
  std::ifstream ifs { R"(data.json)" };

  IStreamWrapper isw { ifs };

  doc.ParseStream( isw );
  ifs.close();

  Value& users = doc["users"];

  Value new_user(rapidjson::kObjectType);

  Value name;
  name.SetString("$@NewUser@$");
  new_user.AddMember("name", name, doc.GetAllocator());

  Value id;
  id.SetInt(user_id);
  new_user.AddMember("id", id, doc.GetAllocator());

  Value messages_for_him;
  messages_for_him.SetArray();
  new_user.AddMember("messages_for_him", messages_for_him, doc.GetAllocator());

  users.PushBack(new_user, doc.GetAllocator());

  FILE* fp = fopen("data.json", "w");

  char buffer[1024];
  FileWriteStream os(fp, buffer, sizeof(buffer));

  Writer<FileWriteStream> writer(os);
  doc.Accept(writer);

  fclose(fp);
  //WorkWithDataFile::Save(doc);

}


int WorkWithDataFile::GetNewId(){
  using namespace rapidjson;
  Document doc;
  std::ifstream ifs { R"(data.json)" };

  IStreamWrapper isw { ifs };

  doc.ParseStream( isw );
  ifs.close();

  Value new_id;

  Value& last_id = doc["last_id"];
  new_id.SetInt(last_id.GetInt() + 1);

  last_id.CopyFrom(new_id, doc.GetAllocator());
  
  FILE* fp = fopen("data.json", "w");


  char buffer[1024];
  FileWriteStream os(fp, buffer, sizeof(buffer));

  Writer<FileWriteStream> writer(os);
  doc.Accept(writer);

  fclose(fp);

 return new_id.GetInt();
}

std::string WorkWithDataFile::GetUserName(int user_id){
    using namespace rapidjson;

    std::string user_name;

    Document doc;
    std::ifstream ifs { R"(data.json)" };

    IStreamWrapper isw { ifs };

    doc.ParseStream( isw );
    ifs.close();

    Value& users = doc["users"];
    for (SizeType i = 0; i < users.Size(); i++){
      if(users[i]["id"].GetInt() == user_id){
        user_name = users[i]["name"].GetString();
        break;
      }
    }

    return user_name;
}