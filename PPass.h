#pragma once
#include <string>
#include <vector>
#include <map>

class PasswordPass {
private:
    std::string homeFolder;
    std::string directFile;
    //bool decyphired;

private:
    PasswordPass(std::string homeFolder, std::string directFile);

public:
    static PasswordPass createAccount();
    static PasswordPass loginIntoAccount();
    static PasswordPass launch();
};

