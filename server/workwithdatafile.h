#ifndef WORKWITHDATAFILE_H
#define WORKWITHDATAFILE_H

#include <string>
#include <vector>
class WorkWithDataFile{
  public:
    static void SetUserName(std::string& new_name, std::string& old_name);
    static std::string GetAllUsers();
    static void SaveMessageForOfflineUser(std::string& _whom_send, std::string&ready_message);
    static std::vector<std::string> GetSavedMessages(std::string& name);
};




#endif