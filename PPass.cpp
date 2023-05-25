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


/*
* ADD TO EVERYTHING IF IT IS EMPTY JUST SHOW ERROR
* 
* i dk maybe add when deleting search by parameteres?
* 
*/

void simulateApp(PasswordPass*& ppass) {
    int option = -1;
    do {
        util::mainMenu();
        option = rangeAnswer(0, 12);
        switch (option) {
            case 0:
                //quit(ppass);
                fmt::print("Are you sure you want to leave? [Y, n]\n> ");
                break;
            case 1:
                ppass->searchPassword(); // done
                break;
            case 2:
                ppass->sortPasswords();
                break;
            case 3:
                ppass->addPassword(); // done
                break;
            case 4:
                ppass->editPassword(); // done 
                break;
            case 5:
                ppass->deletePassword(); // done
                break;
            case 6:
                ppass->addCategory(); // done
                break;
            case 7:
                ppass->deleteCategory(); // done
                break;
            case 8:
                ppass->showCategories(); // done
                break;
            case 9:
                fmt::print(util::white, "\nMaster Password is {} \n", ppass->getPassword()); // done
                break;
            case 10:
                ppass->showPasswords(); // done
                break;
            case 11:
                ppass->showOther(); // done
                break;
            case 12:
                ppass->showPATH();
            default:
                break;

        }

    } while (option != 0);
    fmt::print("end");
    ppass->saveChanges();



}
void PasswordPass::showPATH() {

    fmt::println("{}", pathToFile);
}

void PasswordPass::showOther() {
    fmt::print("\n");
    for (auto el : other) {
        fmt::println("{}", el);
    }
    
}

void PasswordPass::saveChanges() {
    // prepare data to be written to a file
    std::string key = "DECRYPTED";
    char startPassword = 'd';

    std::vector<std::string> dataToWrite;
    dataToWrite.push_back(key);

    for (auto &password : passwordList) {
        std::string data = startPassword + password.getName() + "|" + password.getPassword() + "|" + password.getCategory() + "|" + password.getWebsite() + "|" + password.getLogin();
        dataToWrite.push_back(data);
    }
    int i = 0;
    for (auto el : other) {
        int minToInsert = (int)(i * (passwordList.size() / 3)); // 0 1/3 2/3
        int maxToInsert = (int)((i + 1) * (passwordList.size() / 3)); // 1/3 2/3 3 
        if (minToInsert < 1 ) { minToInsert = 1; }
        int indexToInsert = random(minToInsert, maxToInsert);
        dataToWrite.insert(dataToWrite.begin() + indexToInsert, other.at(other.size() - i - 1));
        fmt::print("\nmin  {} max {} , choosed {}\n", minToInsert, maxToInsert, indexToInsert);
        //dataToWrite.push_back(other.at(i));
        i++;
    }

    // Write data back to a file
    std::fstream outputFile; // Replace "path_to_file.txt" with the actual path to the file
    outputFile.open(pathToFile, std::ios::out);

    if (outputFile.is_open()) {
        for (const auto& data : dataToWrite) {
            outputFile << data << "\n";
        }

        outputFile.close();
        fmt::print(util::white, "\nData successfully written to the file.\n");
    }
    else {
       fmt::print(util::error, "\nError opening the file.\n");
    }

    encryptFile(pathToFile, password);

}

void PasswordPass::deletePassword() {
    //idk jak to kilku usuwac? no po jednemu na raz



    int option = -1;

    do {
        util::deletePasswordMenu(); // change this
        option = rangeAnswer(0, 1);

        switch (option) {
        case 0:
            break;
        case 1: { // delete form list
            fmt::print(util::white, "\nIn the list bellow choose your password to delete\n");
            showPasswords();
            int choice = rangeAnswer(1, passwordList.size()); //  index of object to delete

            fmt::print(util::white, "Password: \n {}", passwordList.at(choice - 1).to_string());



            fmt::print(util::white, "\nAre you sure you want to delete this password? [y,N]\n> ");
            char answer = inputAnswer('y', 'N', false);

            if (answer == 'y') {

                
                passwordList.erase(passwordList.begin() + choice - 1); // Delete password from the vector




                fmt::print(util::white, "You have successfully deleted the password.\n");
            }
            

        }
              break;
          defalt:
              break;
        }
    } while (option != 0);


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

PasswordPass::PasswordPass(std::string pathToFile,  std::string password)
    : pathToFile(pathToFile),  password(password) {}

void PasswordPass::editPassword() {


    int option = -1;

    do {
        util::editPasswordMenu(); // change this
        option = rangeAnswer(0, 1);

        switch (option) {
            case 0:
                break;
            case 1: {
                fmt::print(util::white, "\nIn the list bellow choose your password to edit\n");
                showPasswords();
                int choice = rangeAnswer(1, passwordList.size()); //  index of object to edit

                fmt::print(util::white, "Password: \n {}", passwordList.at(choice - 1).to_string());

                int editing = -1;
                do {

                    util::editingMenu();
                    editing = rangeAnswer(0, 5);

                    switch (editing) {
                        case 0: // out
                        

                            break;
                        case 1: { // category
                            // from active list of categories

                            std::vector<std::string> categories = getAllCategories();

                            showList(categories);
                            int chosedCategory = rangeAnswer(1, categories.size());

                            char answer;
                            fmt::print(util::white, "\nAre you sure you want to change category to {} [y,N]\n> ", categories.at(choice - 1));
                            answer = inputAnswer('y', 'N', false);

                            if (answer == 'y') {
                                fmt::print(util::white, "You`ve successfuly updated category for password");
                                passwordList.at(choice-1).setCategory(categories.at(chosedCategory - 1));
                            }
                        }

                            break;
                        case 2: {// name
                            // asking is already 
                            std::string name = inputType("name");

                            char answer;
                            fmt::print(util::white, "\nAre you sure you want to change name to {} [y,N]\n> ", name);
                            answer = inputAnswer('y', 'N', false);

                            if (answer == 'y') {
                                fmt::print(util::white, "You`ve successfuly updated name for password");
                                passwordList.at(choice-1).setName(name);
                            }


                        }

                            break;
                        case 3: {// password

                        
                            std::string password = inputType("password");

                            passwordStatistics(password);

                            char answer;
                            fmt::print(util::white, "\nAre you sure you want to change password to {} [y,N]\n> ", password);
                            answer = inputAnswer('y', 'N', false);

                            if (answer == 'y') {
                                fmt::print(util::white, "You`ve successfuly updated password for password");
                                passwordList.at(choice-1).setText(password);
                            }
                        }
                            break;
                        case 4: { // login
                            std::string login = inputType("login");

                            char answer;
                            fmt::print(util::white, "\nAre you sure you want to change login to {} [y,N]\n> ", login);
                            answer = inputAnswer('y', 'N', false);

                            if (answer == 'y') {
                                fmt::print(util::white, "You`ve successfuly updated login for password");
                                passwordList.at(choice-1).setLogin(login);
                            }
                        }
                            break;
                        case 5: {// website
                            std::string website = inputType("website");

                            char answer;
                            fmt::print(util::white, "\nAre you sure you want to change website to {} [y,N]\n> ", website);
                            answer = inputAnswer('y', 'N', false);

                            if (answer == 'y') {
                                fmt::print(util::white, "You`ve successfuly updated website for password");
                                passwordList.at(choice-1).setWebsite(website);
                            }
                        }
                            break;
                        default:
                            fmt::print(util::error, "You just got in default case on line 385");
                            break;
                    }

                } while (editing != 0);


            }
                  break;
              defalt:
                break;
        }
    } while (option != 0);

}

void PasswordPass::deleteCategory() {
    int option = -1;

    do {
        util::deleteCategoryMenu();
        option = rangeAnswer(0, 1);

        switch (option) {
        case 0:
            break;
        case 1: {
            std::string category = presentCategory();

            fmt::print(util::white, "\nCategory {} will be deleted with those passwords\n\n", category);

            for (const auto el : getPasswordsByCategory(category)) {
                fmt::print(util::white, "{}\n", el.to_string());
            }

            char answer;
            fmt::print(util::white, "\nAre you sure you want to delete  those passwords [y,N]\n> ");
            answer = inputAnswer('y', 'N', false);

            if (answer == 'y') { deletePasswordsByCategory(category); }


        }
              break;
        }
    } while (option != 0);


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

            if (getAllCategories().size() < 1) {
                fmt::print(util::white, "\nThere are no categories, please create a category first, than proceed\n");
                break;
            }

            // {name, website, login}
            std::vector<std::string> data = templatePassword();

            std::string category;
            std::vector<std::string> categories = getAllCategories();

            showList(categories);
            int choice = rangeAnswer(1, categories.size());
            std::string password = inputType("password");

            //bool isSafe = isPasswordSafe(password);
            //bool isPopular = isPasswordPopular(password);
            //bool used = usedBefore(password);


            passwordStatistics(password);


            char answer;
            fmt::print(util::white, "\nAre you sure you want to leave this passwords [y,N]\n> ");
            answer = inputAnswer('y', 'N', false);
            
            if (answer == 'y') {

                Password ps = Password(data.at(0), password, categories.at(choice-1), data.at(1), data.at(2));
                passwordList.push_back(ps);
                passwordMap[categories.at(choice-1)].push_back(ps);
                fmt::print("\nPassword was created successfully here is overview\n");
                fmt::print(util::white, "{}\n", ps.to_string());
            }

        }
              break;
        case 2: {

            // {name, category, website, login}
            std::vector<std::string> data = templatePassword();
            std::vector<std::string> categories = getAllCategories();

            showList(categories);
            int choice = rangeAnswer(1, categories.size());



            std::string password;

            
            fmt::print(util::white, "\nNow you prompt to autogenerate your password\nGive me length of it\n> ");
            int length = rangeAnswer(8, 40);

            fmt::print(util::white, "\ndoes it have UPPERCASE ? [y, N]\n> ");
            char uppercase = inputAnswer('y', 'N', false);

            fmt::print(util::white, "\ndoes it have $YMB0|$ ? [y,N]\n> ");
            char symbols = inputAnswer('y', 'N', false);

            char answer;

            do {
                password = generateRandomPassword(length, (uppercase == 'y'? true:false), (symbols == 'y' ? true : false) );

                fmt::print(util::white, "Your password is {}\n", password);
                fmt::print(util::white, "Please wait a little bit, we are checking your password");
                passwordStatistics(password);

                fmt::print(util::white, "\nRegenerate Password? [y,N]");
                answer = inputAnswer('y', 'N', false    );

                //apparantly input answer needs to be fixed first try is white second is red

            } while (answer != 'N');

           
            fmt::print(util::white, "\nAre you sure you want to create this password [y,N]");
            answer = inputAnswer('y', 'N', false); // dodatu czy first moze?
            

            if (answer == 'y') {
                Password ps = Password(data.at(0), password, categories.at(choice-1), data.at(1), data.at(2));
                passwordList.push_back(ps);
                passwordMap[categories.at(choice - 1)].push_back(ps);

                fmt::print(util::white, "\nPassword was created successfully here is overview\n");
                fmt::print(util::white, "{}\n", ps.to_string());

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
        if (el.getPassword() == password) {
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
    

    name = inputType("name");
    login = inputType("login");
    website = inputType("website");



    return {name, website, login};
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
    //passwordManager = nullptr;

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


void PasswordPass::deletePasswordsByCategory(const std::string& category) {
    passwordList.erase(
        std::remove_if(
            passwordList.begin(),
            passwordList.end(),
            [&](const Password& password) {
                return password.getCategory() == category;
            }
        ),
        passwordList.end()
                );

    passwordMap.erase(category);

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
    int i = 1;
    for (auto& el : this->getPasswordList()) {
        fmt::print(util::white, "{} {}\n",i++, el.to_string());
    }
}

PasswordPass* PasswordPass::createAccount() {
    fmt::print(util::white, "\nYou`re in process of creaating an account for Password managing\n");
    std::string fileName;
    bool correctName = false;
    std::string password;

    do {
        fmt::print(util::white, "\nGive me a name for the file\n> ");
        std::cin >> fileName;

        // Check if the file name is valid
        if (fileName.empty()) {
            fmt::print(util::white, "File name cannot be empty. Please enter a valid name.\n");
        }
        else if (fileName.find_first_of(R"(/[\\:*?"<>|])") != std::string::npos) {
            fmt::print(util::white, "Invalid characters in the file name. Please enter a valid name.\n");
        }
        else {
            correctName = true;
        }
    } while (!correctName);

    std::filesystem::path path = util::secretFolder / fileName;
    path.replace_extension(".txt");


    std::fstream outputFile(path, std::ios::out);
    if (outputFile.is_open()) {
        outputFile << "DECRYPTED" << std::endl;
        outputFile.close();
        fmt::print(util::white, "\nYour secret file '{}' is created\n", fileName);
    }
    else {
        fmt::print(util::white, "Error creating the file.\n");
    }
    bool correctPassword = false;
    fmt::print(util::white, "\nGive me a master password\n> ");

    do {
        std::cin >> password;
        correctPassword = true;

        if (isNotInSet(password)) {
            correctPassword = false;
            fmt::print(util::error, "\nProvided password has banned characters, try again\n> ");
        }
        
        

    } while (!correctPassword);

    encryptFile(path.string(), password);

    return new PasswordPass(path.string(), password);


}

//void isInAlphabetSet(std::string & str) {
//
//    for (size_t i = 0; i < length; i++)
//    {
//
//    }
//
//}

void setOthers(const std::vector<std::string> vec, PasswordPass* ps) {
    ps->setOther(vec);
}

void setPassList(const std::vector<std::string> dirt, const char delimite, PasswordPass* ps) {
    ps->setPasswordList(passwordList(dirt, delimite));
}

PasswordPass* PasswordPass::loginIntoAccount() {

    //maybe optiization zrobic, zeby input == inputAnswer a nie przez cin
    fmt::print(util::white,"\nWould you like to pick a file from current folder or give a path? [F/P]\n> ");
    char input; 
    std::cin >> input;
    std::string path;
    if (input != 'F' && input != 'P') {input = inputAnswer('F', 'P', true);}
    if (input == 'P') {
        return PasswordPass::loginWithPath("");
    }

    return PasswordPass::loginFromFolder();
}

PasswordPass* PasswordPass::loginFromFolder() {
    if (!secretFolderIS()) {
        char answer;
        fmt::print(util::white,"\nThere is no Folder with secrets\nWould You like to create one or login with path? [C/P]\n> ");
        std::cin >> answer;
        if (answer != 'C' && answer != 'P') { answer = inputAnswer('C', 'P', true); }

        if (answer == 'P') {
            return PasswordPass::loginWithPath("");
        }
        
        if (std::filesystem::create_directory(util::secretFolder)) {
            fmt::print(util::white, "\nDirectory created successfully.\n");
        }
        else {
            fmt::print(util::white, "\nFailed to create directory.\n");
        }
    }

    std::vector<std::string> currentOptions = allSecrets();
    if (currentOptions.size() < 1) { 
        //add here to create them also BUT, ask first teaches because this is not mentioned on project`s site
        fmt::print(util::error, "\nThere is no files in secret Folder\n"); 
    }

    fmt::print(util::white, "\nPlease choose one file from this list.\n");
    showList(currentOptions);
    
    int option = rangeAnswer(1, currentOptions.size());

    std::filesystem::path pathToFile = util::secretFolder;
    pathToFile.append(currentOptions.at(option-1));

    return PasswordPass::loginWithPath(pathToFile.string());
}

PasswordPass* PasswordPass::loginWithPath(std::string autoPath) {
    std::string path;

    if (autoPath.empty()) {
        fmt::print(util::white, "\nPlease provide me with a path to a file\n");
        std::cin >> path;
        if (!std::filesystem::is_regular_file(path)) {
            path = correctPath(path);
        }
    }
    else {
        path = autoPath;
    }
    

    std::string password;
    fmt::print(util::white, "\nPlease provide me with a password to a file\n");
    std::cin >> password;

    bool dec = isDecrypted(path, password);

    if (!dec) {
        password = correctPassword(path);
    }

    std::vector<std::string> decipheredList = decryptFile(path, password);

    std::vector<std::string> others = filter(decipheredList);

    PasswordPass* ppass = new PasswordPass(path, password);
    setOthers(others, ppass);
    setPassList(decipheredList, '|', ppass);
    ppass->populatePasswordMap();
    fmt::print(util::white, "\nLoged successfully pleasant use\n");
    return ppass;
}

PasswordPass* launch() {
    fmt::print(  fmt::fg(fmt::color::snow), "\tHello to PPass aka PasswordPass\nWhould you like to login or create secret file?\n[L/C]\n> ");
    char input;
    std::cin >> input;
    if (input != 'L' && input != 'C') { input = inputAnswer('L', 'C', true); }
    if (input == 'L') { 
        return PasswordPass::loginIntoAccount(); 
    }
    //return  PasswordPass::loginIntoAccount();
    PasswordPass::createAccount();
    return nullptr;

}

PasswordPass::~PasswordPass() {
    // Destructor implementation
    //not usre if i need to clean after those 2 containers
    delete &passwordList;
    delete &passwordMap;
    //delete this;
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
