#include "workwithdatafile.h"
#include <rapidjson/document.h>
#include <rapidjson/istreamwrapper.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/ostreamwrapper.h>
#include <rapidjson/filewritestream.h>
#include "rapidjson/filereadstream.h"
#include <fstream>
#include <cstring>
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
      if (!std::strcmp(users[i][0].GetString(), old_name.c_str()) || !std::strcmp(users[i][0].GetString(), new_name.c_str())){
        users[i][0] = name;
        this_new_user = false;
        break;
      }
    }

    if(this_new_user){
      users.PushBack(name, doc.GetAllocator());
    }


    FILE* fp = fopen("data.json", "w"); // non-Windows use "w"

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
      all_users += users[i][0].GetString();
      all_users += "\n";
    }

    return all_users;

}