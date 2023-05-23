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



//Handling of any type of errors, repeated questions to users or maybe any other little stuff like split() separate to another file



void simulateApp(PasswordPass*& ppass) {
    int option = -1;
    do {
        util::mainMenu();
        option = rangeAnswer(0, 8);
        switch (option) {
            case 0:
                quit(ppass);
                break;
            case 1:
                ppass->searchPassword();
                break;
            case 2:
                ppass->sortPasswords();
                break;
            case 3:
                ppass->addPassword();
                break;
            case 4:
                ppass->editPassword();
                break;
            case 5:
                ppass->deletePassword();
                break;
            case 6:
                ppass->addCategory();
                break;
            case 7:
                ppass->deleteCategory();
                break;
            case 8:
                ppass->showCategories();
                break;
            default:
                break;


        }

    } while (option != 0);
    
}

void PasswordPass::deletePassword() {

}



void PasswordPass::sortPasswords() {

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
                std::vector<Password> nameSearch = byAttribute(passwordList, name, SearchOption::ByName);

                if (nameSearch.empty()) { fmt::print(util::error, "No passwords for '{}'", name); break; }

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

                std::vector<Password> loginSearch = byAttribute(passwordList, login, SearchOption::ByLogin);

                if (loginSearch.empty()) { fmt::print(util::error, "No passwords for '{}'", login); break; }

                fmt::print(util::white, "\nThese passwords i found by category {}\n", login);
                for (auto el : loginSearch) {
                    fmt::print(util::white, "{}\n", el.to_string());
                }
                break;
            }
            case 4: {
                std::string webSite;
                fmt::print(util::white, "\nPlease provide me with a login for password to be founded in\n ");
                std::cin >> webSite;

                std::vector<Password> websiteSearch = byAttribute(passwordList, webSite, SearchOption::ByWebSite);

                if (websiteSearch.empty()) { fmt::print(util::error, "No passwords for '{}'", webSite); break; }

                fmt::print(util::white, "\nThese passwords i found by category {}\n", webSite);
                for (auto el : websiteSearch) {
                    fmt::print(util::white, "{}\n", el.to_string());
                }
            }
                break;
            case 5: {
                std::string category = "";
                fmt::print(util::white, "\nPlease provide me with an information for every field\nIf you don`t want this field to be included place '-'\n ");
                fmt::print(util::white, "\nGive me category for this password\n ");
                std::cin >> category;

                std::string name = "";
                fmt::print(util::white, "\nGive me name for this password\n ");
                std::cin >> name;

                std::string login = "";
                fmt::print(util::white, "\nGive me login for this password\n ");
                std::cin >> login;

                std::string website = "";
                fmt::print(util::white, "\nGive me website for this password\n ");
                std::cin >> website;

                


                std::vector<Password> passwords;
                //fmt::print(util::white, "\nFor parameters \nCategory: {}\nName: {}\nLogin: {}\nWebSite: {}\n We founded this/those passwords:\n", category, name, login, website);

                //std::cout << "\nFor parameters \nCategory: " << category << "\nName: " << name << "\nLogin: " << login << "\nWebSite: " << website << "\n We founded this/those passwords:\n";


                if (category.at(0) != '-') {

                    passwords = getPasswordsByCategory(category);

                    if (name.at(0) != '-' && passwords.size() > 1 ) {
                        passwords = byAttribute(passwords, name, SearchOption::ByName);
                    }

                    if (login.at(0) != '-' && passwords.size() > 1) {
                        passwords = byAttribute(passwords, login, SearchOption::ByLogin);

                    }

                    if (website.at(0) != '-' && passwords.size() > 1) {
                        passwords = byAttribute(passwords, website, SearchOption::ByWebSite);

                    }
                    

                } else if (name.at(0) != '-') {
                    passwords = byAttribute(passwordList, name, SearchOption::ByName);

                    if (login.at(0) != '-' && passwords.size() > 1) {
                        passwords = byAttribute(passwords, login, SearchOption::ByLogin);

                    }

                    if (website.at(0) != '-' && passwords.size() > 1) {
                        passwords = byAttribute(passwords, website, SearchOption::ByWebSite);

                    }

                }
                else if (login.at(0) != '-') {
                    passwords = byAttribute(passwordList, login, SearchOption::ByLogin);

                    if (website.at(0) != '-' && passwords.size() > 1) {
                        passwords = byAttribute(passwords, website, SearchOption::ByWebSite);

                    }
                }
                else if (website.at(0) != '-') {
                    passwords = byAttribute(passwordList, website, SearchOption::ByWebSite);
                } else {
                    fmt::print(util::white, "\nNo fields were provided\n");
                    break;
                }

                fmt::print(util::white, "\nFor parameters \nCategory: {}\nName: {}\nLogin: {}\nWebSite: {}\n We founded this/those passwords:\n", category, name, login, website);

                for (auto el : passwords) {
                    fmt::print(util::white, "\n{}", el.to_string());
                }

            }
                break;
            default:
                fmt::print(util::white, "Invalid choice. In searchPassword() option : {}\n", option);
                break;

        }
    } while (option != 0);
}


std::vector<Password> byAttribute(const std::vector<Password> vec,const std::string nameOfAttribute, const SearchOption so) {

    std::vector<Password> found;


    switch (so) {
        case SearchOption::ByName: {
                for (const auto el : vec) {
                    if (nameOfAttribute == el.getName()) {
                        found.push_back(el);
                    }
                }
                break;
        }
        case SearchOption::ByLogin: {
            for (const auto el : vec) {
                if (nameOfAttribute == el.getLogin()) {
                    found.push_back(el);
                }
            }
            break;
        }
        case SearchOption::ByWebSite: {
            for (const auto el : vec) {
                if (nameOfAttribute == el.getWebsite()) {
                    found.push_back(el);
                }
            }
            break;
        }
    }


    
    return found;
}

PasswordPass::PasswordPass(std::string pathToFile, std::vector<std::string> other)
    : pathToFile(pathToFile), other(other) {}



void PasswordPass::editPassword() {

}

void PasswordPass::deleteCategory() {


}

void PasswordPass::addCategory() {
    int option = -1;

    do {
        util::addCategoryMenu();
        option = rangeAnswer(0, 1);

        switch (option) {
        case 0:
            break;
        case 1: {
            std::string category = uniqueCategory();

            fmt::print(util::white, "\nCreated a category: {}\n", category);


            passwordMap.insert(std::make_pair(category, std::vector<Password>()));

            
        }
              break;
        }
    } while (option != 0);
}


    

void PasswordPass::addPassword() {
    int option = -1;

    do {
        util::addPasswordMenu();
        option = rangeAnswer(0, 2);

        switch (option) {
        case 0:
            break;
        case 1: {
            // {name, category, website, login}
            std::vector<std::string> data = templatePassword();

            std::string password = inputType("password");

            bool isSafe = isPasswordSafe(password);
            bool isPopular = isPasswordPopular(password);
            bool used = usedBefore(password);


            fmt::print((isSafe?util::white : util::error), "\nYour password is {}", (isSafe ? "safe\n" : "not safe\n"));
            fmt::print((isPopular ? util::error : util::white), "\nYour password is {}", (isPopular ? "popular\n" : "not popular\n"));
            fmt::print((used ? util::error : util::white), "\nYour password was {}", (used ? "used\n" : "not used\n"));


            char answer;
            fmt::print(util::white, "\nAre you sure you want to leave this passwords [y,N]");
            answer = inputAnswer('y', 'N');
            
            if (answer == 'y') {
                Password ps = Password(data.at(0), password, data.at(1), data.at(2), data.at(3));
                passwordList.push_back(ps);
                passwordMap[data.at(1)].push_back(ps);

            } 

        }
              break;
        case 2: {

            // {name, category, website, login}
            std::vector<std::string> data = templatePassword();
            std::string password;

            
            fmt::print(util::white, "\nNow you prompt to autogenerate your password\nGive me length of it\n> ");
            int length = rangeAnswer(8, 40);

            fmt::print(util::white, "\ndoes it have UPPERCASE ?\n [y, N]> ");
            char uppercase = inputAnswer('y', 'N');

            fmt::print(util::white, "\ndoes it have $YMB0|$ ?\n> [y,N]");
            char symbols = inputAnswer('y', 'N');

            char answer;

            do {
                password = generateRandomPassword(length, (uppercase == 'y'? true:false), (symbols == 'y' ? true : false) );

                fmt::print(util::white, "Your password is {}\n", password);

                passwordStatistics(password);

                fmt::print(util::white, "\nRegenerate Password? [y,N]");
                answer = inputAnswer('y', 'N');

                //apparantly input answer needs to be fixed first try is white second is red

            } while (answer != 'N');

           
            fmt::print(util::white, "\nAre you sure you want to create this password [y,N]");
            answer = inputAnswer('y', 'N');
            

            if (answer == 'y') {
                Password ps = Password(data.at(0), password, data.at(1), data.at(2), data.at(3));
                passwordList.push_back(ps);
                passwordMap[data.at(1)].push_back(ps);

            }

        }
            break;

        default:
            fmt::print(util::white, "Invalid choice. In searchPassword() option : {}\n", option);
            break;

        }
    } while (option != 0);
}

void PasswordPass::passwordStatistics(const std::string password) {
    bool isSafe = isPasswordSafe(password);
    bool isPopular = isPasswordPopular(password);
    bool used = usedBefore(password);


    fmt::print((isSafe ? util::white : util::error), "\nYour password is {}", (isSafe ? "safe\n" : "not safe\n"));
    fmt::print((isPopular ? util::error : util::white), "\nYour password is {}", (isPopular ? "popular\n" : "not popular\n"));
    fmt::print((used ? util::error : util::white), "\nYour password was {}", (used ? "used\n" : "not used\n"));

}

bool PasswordPass::usedBefore(const std::string password) {

    bool used = false;

    for (const auto &el : passwordList) {
        if (el.getText() == password) {
            used = true;
            break;
        }
    }
    return used;

}


std::vector<std::string> templatePassword() {
    fmt::print(util::white, "\nYou must provide me with at least name and category for password:\n");

    std::string name;
    std::string login;
    std::string website;
    std::string category;

    category = inputType("category");
    name = inputType("name");
    login = inputType("login");
    website = inputType("website");

    return {name, category, website, login};
}

std::string inputType(std::string type) {
    fmt::print(util::white, "\nGive me {} for password:\n ", type);
    std::string attribute;
    std::cin >> attribute;

    while (attribute == "-" || attribute.length() < 2) {
        fmt::print(util::error, util::Fault, type);
        std::cin >> attribute;
    }
    
    return attribute;
}

bool isPasswordPopular(const std::string& password) {

    std::string line;

    auto stream = std::fstream("rockyou.txt");

    bool popular = false;

    //int i = 0;
    while (getline(stream, line)) {
        //fmt::print("{} ", i++);
        if (password == line) {
            popular = true;
            break;
        }
    }

    return popular;

}

bool isPasswordSafe(const std::string& password) {
    if (password.length() < 8) {
        return false;

    }

    bool hasUppercase = false;
    bool hasLowercase = false;
    bool hasDigit = false;

    for (char ch : password) {
        if (std::isupper(ch)) {
            hasUppercase = true;
        }
        else if (std::islower(ch)) {
            hasLowercase = true;
        }
        else if (std::isdigit(ch)) {
            hasDigit = true;
        }
    }

    return hasUppercase && hasLowercase && hasDigit;
}


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

std::vector<Password> PasswordPass::getPasswordsByCategory(const std::string& category) {
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

//unfinished and not sure if needed
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
    fmt::print(util::white, "\nLoged successfully pleasant use\n");
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
