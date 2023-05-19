#pragma once
#include <string>
#include <vector>
#include <map>


class PasswordPass {
private:
    //std::vector<Password> decypheredList;
    std::string homeFolder;
    std::string directFile;
   

private:
    PasswordPass(std::string homeFolder, std::string directFile);

public:
    static PasswordPass createAccount();
    static PasswordPass loginIntoAccount();
    static PasswordPass launch();

    ~PasswordPass();
};

