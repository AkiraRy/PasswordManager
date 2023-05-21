#define FMT_HEADER_ONLY
#include "PPass.h"
#include "Decryption.h"
#include "Encryption.h"
#include "Password.h"
#include "Utilities.h"
#include <fmt/core.h>
#include <fmt/color.h>
#include <iostream>
#include <vector>
#include <map>
#include <filesystem>
#include <fstream>
#include <regex>

// i ended up on searching function, please fix this getPasswordsBy categegory thank you;
//maybe divide seacrhTemplate into 2 chunks 1 for category 1 for other stuff


enum class SearchOption {
    ByName,
    ByCategory
};

//Handling of any type of errors, repeated questions to users or maybe any other little stuff like split() separate to another file

// maybe try to place if in logniwithPath for handling login from both folder and path, but in folder ver path is already provdided


void simulateApp(PasswordPass*& ppass) {
    int option = -1;
    do {
        util::mainMenu();
        option = rangeAnswer(0, 7);
        switch (option) {
            case 0:
                quit(ppass);
                break;
            case 1:
                ppass->searchPassword();
                break;

        }

    } while (option != 0);
    
}


void PasswordPass::searchPassword() {
    int option = -1;

    do {
        util::searchMenu();
        option = rangeAnswer(0, 5);

        switch (option) {
            case 0:
                break;
            case 1: {
                std::string category;
                fmt::print(util::white, "\nPlease provide me with a category for password to be founded in\n ");
                std::cin >> category;
                std::vector<Password> categorySearch = getPasswordsByCategory(category);
                if (categorySearch.empty()) { fmt::print(util::error, "No passwords for '{}'", category); }
                fmt::print(util::white, "\nThese passwords i found by category {}\n", category);
                for (auto el : categorySearch) {
                    fmt::print(util::white, "{}\n", el.to_string());
                }
                break;
            }
            case 2: {
                std::string name;
                fmt::print(util::white, "\nPlease provide me with a name for password to be founded\n ");
                std::cin >> name;
                std::vector<Password> nameSearch = byName(passwordList, name);

                if (nameSearch.empty()) { fmt::print(util::error, "No passwords for '{}'", name); }

                fmt::print(util::white, "\nThese passwords i found by name {}\n", name);
                for (auto el : nameSearch) {
                    fmt::print(util::white, "{}\n", el.to_string());
                }
                break;
            }
            case 3: {
                std::string login;
                fmt::print(util::white, "\nPlease provide me with a login for password to be founded in\n ");
                std::cin >> login;
                std::vector<Password> loginSearch = getPasswordsByCategory(login);
                if (loginSearch.empty()) { fmt::print(util::error, "No passwords for '{}'", login); }
                fmt::print(util::white, "\nThese passwords i found by category {}\n", login);
                for (auto el : loginSearch) {
                    fmt::print(util::white, "{}\n", el.to_string());
                }
                break;
            }
            case 4:
                break;
            case 5:
                break;
            default:
                fmt::print(util::white, "Invalid choice. In searchPassword() option : {}\n", option);
                break;


        }
    } while (option != 0);
}

//dodatu enum
void searchTemplate(std::string type, SearchOption so, std::vector<Password> vec) {
    std::string input; // name or category
    fmt::print(util::white, "\nPlease provide me with a {} for password to be founded in\n ", type);
    std::cin >> input;
    std::vector<Password> typeSearch;

    switch (so) {
        case SearchOption::ByName: {
            typeSearch = byName(vec, input);
            break;
        }
        case SearchOption::ByCategory:  {
            typeSearch = 
        }
    }

    if (typeSearch.empty()) { 
        fmt::print(util::error, "No passwords for '{}'", input); 
        return; 
    }
    fmt::print(util::white, "\nThese passwords i found by {}:  {}\n", type, input);
    for (auto el : typeSearch) {
        fmt::print(util::white, "{}\n", el.to_string());
    }

}

std::vector<Password> byName(const std::vector<Password> vec,const std::string name) {

    std::vector<Password> found;

    for (const auto el : vec) {
        if (name == el.getName()) {
            found.push_back(el);
        }
    }
    return found;
}

PasswordPass::PasswordPass(std::string pathToFile, std::vector<std::string> other)
    : pathToFile(pathToFile), other(other) {}

/*
void sortPasswords();

void changePassword();

void removeDirectory();

void addCategory();
    
void isPasswordSafe();

void createPassword();

void PasswordPass::searchPassword() {

}

*/


//call it at the end
void quit(PasswordPass*& passwordManager) {
    // ALSO ADD HERE WRITE TO FILE TO SAVE ALL CHANGES.

    // Delete the PasswordPass object
    delete passwordManager;

    std::cout << "Goodbye!\n";

    
}

void PasswordPass::populatePasswordMap() {
    passwordMap.clear(); // Clear the map before populating it

    for (const Password& password : passwordList) {
        const std::string& category = password.getCategory();
        passwordMap[category].push_back(password);
    }
}

std::vector<std::string> PasswordPass::getAllCategories() const {
    std::vector<std::string> categories;

    for (const auto& entry : passwordMap) {
        categories.push_back(entry.first);
    }

    return categories;
}

std::vector<Password> getPasswordsByCategory(const std::map<std::string, std::vector<Password>>& passwordMap, const std::string& category) {
    static const std::vector<Password> emptyPasswords; // Empty vector to return if category not found

    auto it = passwordMap.find(category);
    if (it != passwordMap.end()) {
        return it->second; // returns an password with category
    }

    return emptyPasswords; // returns nothing if there is no such category
}

void PasswordPass::showCategories() {
    for (auto el : this->getAllCategories() ) {
        std::cout << el << std::endl;
    }
}

void PasswordPass::showPasswords() {
    for (auto& el : this->getPasswordList()) {
        std::cout << el.to_string() << std::endl;
    }
}

//unfinished and not sure if needed(for additional point maybe)
void PasswordPass::createAccount() {
    std::string path_str;
    fmt::print( "Wprowadż sczieżke do pliku lub folderu z plikami szyfrowanymi\n: ");
    std::cin >> path_str;
    std::filesystem::path path_obj(path_str);

    if (std::filesystem::is_directory(path_obj)) {
        std::cout << "The path is a directory." << std::endl;
        //return PasswordPass();
    }
    else if (std::filesystem::is_regular_file(path_obj)) {
        std::cout << "The path is a regular file." << std::endl;
        //return PasswordPass();
    }
    else {
        std::cout << "The path does not exist, Please make sure that given path is correct" << std::endl;
        //return PasswordPass();
    }
}

void setPassList(const std::vector<std::string> dirt, const char delimite, PasswordPass* ps) {
    ps->setPasswordList(passwordList(dirt, delimite));
}

PasswordPass* PasswordPass::loginIntoAccount() {
    fmt::print(util::white,"\nWould you like to pick a file from current folder or give a path? [F/P]\n> ");
    char input; 
    std::cin >> input;
    std::string path;
    if (input != 'F' && input != 'P') {input = inputAnswer('F', 'P');}
    if (input == 'P') {
        return PasswordPass::loginWithPath("");
    }

    return PasswordPass::loginFromFolder();
}

PasswordPass* PasswordPass::loginFromFolder() {
    if (!secretFolderIS()) {
        char answer;
        fmt::print(util::white,"There is no Folder with secrets\nWould You like to create one or login with path? [C/P]\n> ");
        std::cin >> answer;
        if (answer != 'C' && answer != 'P') { answer = inputAnswer('C', 'P'); }

        if (answer == 'P') {
            return PasswordPass::loginWithPath("");
        }
        
        if (std::filesystem::create_directory(util::secretFolder)) {
            fmt::print(util::white, "Directory created successfully.");
        }
        else {
            fmt::print(util::white, "Failed to create directory.");
        }
    }

    std::vector<std::string> currentOptions = allSecrets();
    if (currentOptions.size() < 1) { 
        //add here to create them also BUT, ask first teaches because this is not mentioned on project`s site
        fmt::print(util::error, "There is no files in secret Folder"); 
    }

    fmt::print(util::white, "\nPlease choose one file from this list.\n");
    showFiles(currentOptions);
    
    int option = rangeAnswer(1, currentOptions.size());

    std::filesystem::path pathToFile = util::secretFolder;
    pathToFile.append(currentOptions.at(option-1));

    return PasswordPass::loginWithPath(pathToFile.string());
}

PasswordPass* PasswordPass::loginWithPath(std::string autoPath) {
    std::string path;

    if (autoPath.empty()) {
        fmt::print(util::white, "Please provide me with a path to a file\n");
        std::cin >> path;
        if (!std::filesystem::is_regular_file(path)) {
            path = correctPath(path);
        }
    }
    else {
        path = autoPath;
    }
    

    std::string password;
    fmt::print(util::white, "Please provide me with a password to a file\n");
    std::cin >> password;

    bool dec = isDecrypted(path, password);

    if (!dec) {
        password = correctPassword(path);
    }

    std::vector<std::string> decipheredList = decryptFile(path, password);

    std::vector<std::string> others = filter(decipheredList);

    PasswordPass* ppass = new PasswordPass(path, others);
    setPassList(decipheredList, '|', ppass);
    ppass->populatePasswordMap();
    fmt::print(util::white, "\nLoged successfully pleasant useю\n");
    return ppass;
}

PasswordPass* launch() {
    fmt::print(  fmt::fg(fmt::color::snow), "\tHello to PPass aka PasswordPass\nWhould you like to login or create secret file?\n[L/C]\n> ");
    char input;
    std::cin >> input;
    if (input != 'L' && input != 'C') { input = inputAnswer('L', 'C'); }
    if (input == 'L') { 
        return PasswordPass::loginIntoAccount(); 
    }
    return  PasswordPass::loginIntoAccount();
}

PasswordPass::~PasswordPass() {
    // Destructor implementation
    //not usre if i need to clean after those 2 containers
    delete &passwordList;
    delete &passwordMap;
    delete this;
}

/*
for checking if string is empty and if yes i will write there a timestamp also timestamp will start with TSMP-{timestamp} in ordere like hh - mm - ss
but i need ask if i store only 1 timestamp or more?
and in case of wrong password i write same or jsut write wrong password;

std::ifstream file("secret.txt"); // Open the file for reading
    std::vector<std::string> lines; // Vector to store the lines

    std::string line;
    while (std::getline(file, line)) {
        lines.push_back(line);
    }

    // Print the lines
    for (const auto& line : lines) {
        fmt::print("{}  isempty? {} \n", line, line.empty());
    }
    fmt::print("{}", lines.size());
*/
