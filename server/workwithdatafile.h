#ifndef WORKWITHDATAFILE_H
#define WORKWITHDATAFILE_H

#include <string>
#include <vector>

#include <rapidjson/document.h>


class WorkWithDataFile{
  public:
//    static void SetUserName(std::string& new_name, std::string& old_name);
    static void ChangeUserName(int user_id, std::string& new_name);
    static std::string GetAllUsers();
    static void SaveMessageForOfflineUser(int user_id, std::string&ready_message);
    static std::vector<std::string> GetSavedMessages(int user_id);
    static int GetNewId();
    static void CreateNewUser(int user_id);
    static std::string GetUserName(int user_id);
//  private:
//    static void Save(rapidjson::Document& doc);
};




#endif