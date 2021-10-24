#ifndef WORKWITHDATAFILE_H
#define WORKWITHDATAFILE_H

#include <string>

class WorkWithDataFile{
  public:
    static void SetUserName(std::string& new_name, std::string& old_name);
    static std::string GetAllUsers();

};




#endif