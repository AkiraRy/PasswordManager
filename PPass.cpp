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

void simulateApp(PasswordPass*& ppass) {
    int option = -1;
    do {
        util::mainMenu();
        option = rangeAnswer(0, 12);
        switch (option) {
        case 0: {
            fmt::print(util::white, "\nAre you sure you want to leave? [Y, n]\n> ");
            char answer = inputAnswer('y', 'n', false);
            if (answer == 'n') { option = -1; }
        }
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
            case 9:
                fmt::print(util::white, "\nMaster Password is {} \n", ppass->getPassword()); 
                break;
            case 10:
                ppass->showPasswords(); 
                break;
            case 11:
                ppass->showOther(); 
                break;
            case 12:
                ppass->showPATH();
                break;
            default:
                break;

        }

    } while (option != 0);
    ppass->saveChanges();



}

void PasswordPass::showPATH() {
    fmt::println("{}", pathToFile);
}

void PasswordPass::showOther() {
    if (other.empty()) { fmt::print(util::error, "\nOther List Is Empty.\n"); return; }

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
        int minToInsert = (int)(i * (passwordList.size() / 4)); // 0 1/4 2/4 3/4
        int maxToInsert = (int)((i + 1) * (passwordList.size() / 4)); // 1/4 2/4 3/4 4 
        if (minToInsert < 1 ) { minToInsert = 1; }
        if (minToInsert == maxToInsert) { maxToInsert++; }
        int indexToInsert = random(minToInsert, maxToInsert);
        dataToWrite.insert(dataToWrite.begin() + indexToInsert, other.at(other.size() - i - 1));
        i++;
        if (i == 4) { break; }
    }

    if (dataToWrite.empty()) { fmt::print(util::error, "\nNothing to writ\n"); return; }

    // Write data back to a file
    std::fstream outputFile; 
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
    int option = -1;

    do {
        util::deletePasswordMenu();
        option = rangeAnswer(0, 1);

        switch (option) {
        case 0:
            break;
        case 1: { // delete form list
            if (passwordList.empty()) { fmt::print(util::error, "Password List Is Empty."); break; }
            fmt::print(util::white, "\nIn the list bellow choose your password to delete\n");
            showPasswords();
            int choice = rangeAnswer(1, passwordList.size()); //  index of object to delete

            fmt::print(util::white, "Password: \n {}", passwordList.at(choice - 1).to_string());

            fmt::print(util::white, "\n\nAre you sure you want to delete this password? [y,N]\n\n> ");
            char answer = inputAnswer('y', 'N', false);

            if (answer == 'y') {                
                passwordList.erase(passwordList.begin() + choice - 1); // Delete password from the vector

                fmt::print(util::white, "\nYou have successfully deleted the password.\n");
            }
        }
              break;
          default:
              break;
        }
    } while (option != 0);


}

void PasswordPass::sortPasswords() {
    int option = -1;

    do {
        util::sortMenu(); 
        option = rangeAnswer(0, 5);

        switch (option) {
            case 0:
                break;
            case 1:
                helpSort({ "category" });
                break;
            case 2:
                helpSort({ "name" });
                break;
            case 3:
                helpSort({ "website" });
                break; 
            case 4:
                helpSort({ "login" });
                break; 
            case 5: 
                helpSort({ "category", "name" });
                break;
            default:
                break;
        }
    } while (option != 0);
    

}   

void PasswordPass::helpSort(const std::vector<std::string> sortFields) {
    auto sortingPredicate = [sortFields](const Password& pass1, const Password& pass2) {
        for (const auto& field : sortFields) {
            if (field == "name" && pass1.getName() != pass2.getName()) {
                return pass1.getName() < pass2.getName();
            }
            if (field == "password" && pass1.getPassword() != pass2.getPassword()) {
                return pass1.getPassword() < pass2.getPassword();
            }
            if (field == "category" && pass1.getCategory() != pass2.getCategory()) {
                return pass1.getCategory() < pass2.getCategory();
            }
            if (field == "website" && pass1.getWebsite() != pass2.getWebsite()) {
                return pass1.getWebsite() < pass2.getWebsite();
            }
            if (field == "login" && pass1.getLogin() != pass2.getLogin()) {
                return pass1.getLogin() < pass2.getLogin();
            }
        }
        return false; // Maintain the original order if all fields are equal
    };

    std::sort(passwordList.begin(), passwordList.end(), sortingPredicate);

    for (const auto& password : passwordList) {
        fmt::print("{}\n", password.to_string());
    }
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
                fmt::print(util::white, "\nPlease provide me with a category for password to be founded in\n\n> ");
                std::cin >> category;
                std::vector<Password> categorySearch = getPasswordsByCategory(category);
                if (categorySearch.empty()) { fmt::print(util::error, "\nNo passwords for '{}'\n", category); break; }
                fmt::print(util::white, "\nThese passwords i found by category {}\n", category);
                for (auto el : categorySearch) {
                    fmt::print(util::white, "{}\n", el.to_string());
                }
                break;
            }
            case 2: {
                std::string name;
                fmt::print(util::white, "\nPlease provide me with a name for password to be founded\n\n> ");
                std::cin >> name;
                std::vector<Password> nameSearch = byAttribute(passwordList, name, SearchOption::ByName);

                if (nameSearch.empty()) { fmt::print(util::error, "\nNo passwords for '{}'\n", name); break; }

                fmt::print(util::white, "\nThese passwords i found by name {}\n", name);
                for (auto el : nameSearch) {
                    fmt::print(util::white, "{}\n", el.to_string());
                }
                break;
            }
            case 3: {
                std::string login;
                fmt::print(util::white, "\nPlease provide me with a login for password to be founded in\n\n> ");
                std::cin >> login;

                std::vector<Password> loginSearch = byAttribute(passwordList, login, SearchOption::ByLogin);

                if (loginSearch.empty()) { fmt::print(util::error, "\nNo passwords for '{}'\n", login); break; }

                fmt::print(util::white, "\nThese passwords i found by category {}\n", login);
                for (auto el : loginSearch) {
                    fmt::print(util::white, "{}\n", el.to_string());
                }
                break;
            }
            case 4: {
                std::string webSite;
                fmt::print(util::white, "\nPlease provide me with a login for password to be founded in\n\n> ");
                std::cin >> webSite;

                std::vector<Password> websiteSearch = byAttribute(passwordList, webSite, SearchOption::ByWebSite);

                if (websiteSearch.empty()) { fmt::print(util::error, "\nNo passwords for '{}'\n", webSite); break; }

                fmt::print(util::white, "\nThese passwords i found by category {}\n", webSite);
                for (auto el : websiteSearch) {
                    fmt::print(util::white, "{}\n", el.to_string());
                }
                break;
            }
            case 5: {
                fmt::print(util::white, "\nPlease provide me with an information for every field\nIf you don`t want this field to be included place '-'\n ");
                std::string category = inputType("category");
                std::string name = inputType("name");
                std::string login = inputType("login");
                std::string website = inputType("website");


                std::vector<Password> passwords;

                if (category.at(0) != '-') {

                    passwords = getPasswordsByCategory(category);
                    if (passwords.empty()) { fmt::print(util::error, "No categories where found for {}", category); break; }
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
                    if (passwords.empty()) { fmt::print(util::error, "No passwords with name where found for {}", name); break; }
                    if (login.at(0) != '-' && passwords.size() > 1) {
                        passwords = byAttribute(passwords, login, SearchOption::ByLogin);

                    }

                    if (website.at(0) != '-' && passwords.size() > 1) {
                        passwords = byAttribute(passwords, website, SearchOption::ByWebSite);

                    }

                }
                else if (login.at(0) != '-') {
                    passwords = byAttribute(passwordList, login, SearchOption::ByLogin);
                    if (passwords.empty()) { fmt::print(util::error, "No passwords with login where found for {}", login); break; }

                    if (website.at(0) != '-' && passwords.size() > 1) {
                        passwords = byAttribute(passwords, website, SearchOption::ByWebSite);

                    }
                }
                else if (website.at(0) != '-') {
                    passwords = byAttribute(passwordList, website, SearchOption::ByWebSite);
                    if (passwords.empty()) { fmt::print(util::error, "No passwords with website where found for {}", website); break; }

                } else {
                    fmt::print(util::white, "\nNo fields were provided\n");
                    break;
                }

                if (passwords.empty()) { fmt::print(util::error, "No passwords were found"); break; }

                fmt::print(util::white, "\nFor parameters \nCategory: {}\nName: {}\nLogin: {}\nWebSite: {}\n We founded this/those passwords:\n", category, name, login, website);

                for (auto el : passwords) {
                    fmt::print(util::white, "\n{}", el.to_string());
                }

            }
                break;
            default: {
                fmt::print(util::white, "\nInvalid choice. In searchPassword() option : {}\n", option);
                break;
            }
        }

    } while (option != 0);
}

std::vector<Password> byAttribute(const std::vector<Password> vec,const std::string nameOfAttribute, const SearchOption so) {

    std::vector<Password> found;
    if (vec.size() < 1) { return found; }
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

PasswordPass::PasswordPass(const std::string pathToFile,const  std::string password)
    : pathToFile(pathToFile),  password(password) {}

void PasswordPass::editPassword() {
    int option = -1;

    do {
        util::editPasswordMenu();
        option = rangeAnswer(0, 1);

        switch (option) {
            case 0:
                break;
            case 1: {
                if (passwordList.size() < 1) { fmt::print(util::error, "\nNo passwords Were Found.\n");  break; }
                fmt::print(util::white, "\nIn the list bellow choose your password to edit\n");
                showPasswords();
                int choice = rangeAnswer(1, passwordList.size()); //  index of object to edit

                fmt::print(util::white, "Password: \n {}", passwordList.at(choice - 1).to_string());

                int editing = -1;
                do {
                    //while loop to edit variables in password
                    util::editingMenu();
                    editing = rangeAnswer(0, 5);

                    switch (editing) {
                        case 0:
                            break;
                        case 1: { // category
                            // from active list of categories

                            std::vector<std::string> categories = getAllCategories();
                            if (categories.size() < 1) { fmt::print(util::error, "\nNo categories were found.\n"); break; }
                            showList(categories);
                            int chosedCategory = rangeAnswer(1, categories.size());

                            char answer;
                            fmt::print(util::white, "\nAre you sure you want to change category to {} [y,N]\n> ", categories.at(choice - 1));
                            answer = inputAnswer('y', 'N', false);

                            if (answer == 'y') {
                                fmt::print(util::white, "\nYou`ve successfuly updated category for password\n");
                                passwordList.at(choice-1).setCategory(categories.at(chosedCategory - 1));
                            }
                        }

                            break;
                        case 2: {// name
                            std::string name = inputType("name");

                            char answer;
                            fmt::print(util::white, "\nAre you sure you want to change name to {} [y,N]\n> ", name);
                            answer = inputAnswer('y', 'N', false);

                            if (answer == 'y') {
                                fmt::print(util::white, "\nYou`ve successfuly updated name for password\n");
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
                            fmt::print(util::error, "\nYou`ve just got in default case on line 385\n");
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
            if (getAllCategories().size() < 1) { fmt::print(util::white, "No categories were found."); break; }

            std::string category = presentCategory();

            fmt::print(util::white, "\nCategory {} will be deleted with those passwords\n\n", category);

            for (const auto el : getPasswordsByCategory(category)) {
                fmt::print(util::white, "{}\n", el.to_string());
            }

            char answer;
            fmt::print(util::white, "\nAre you sure you want to delete those passwords [y,N]\n> ");
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
            std::cin.ignore();

            std::string password;

            
            fmt::print(util::white, "\nNow you prompt to auto-generate your password\nGive me length of it\n");
            int length = rangeAnswer(8, 40);
            std::cin.ignore();

            fmt::print(util::white, "\ndoes it have UPPERCASE ? [y, N]\n\n> ");
            char uppercase = inputAnswer('y', 'N', false);
            std::cin.ignore();

            fmt::print(util::white, "\ndoes it have $YMB0|$ ? [y,N]\n\n> ");
            char symbols = inputAnswer('y', 'N', false);
            std::cin.ignore();

            char answer;

            do {
                password = generateRandomPassword(length, (uppercase == 'y'? true:false), (symbols == 'y' ? true : false) );

                fmt::print(util::white, "Your password is {}\n", password);
                fmt::print(util::white, "\nPlease wait a little bit, we are checking your password\n");
                passwordStatistics(password);

                fmt::print(util::white, "\nRegenerate Password? [y,N]\n\n> ");
                answer = inputAnswer('y', 'N', false);


            } while (answer != 'N');

           
            fmt::print(util::white, "\nAre you sure you want to create this password [y,N]\n\n> ");
            answer = inputAnswer('y', 'N', false);            

            if (answer == 'y') {
                Password ps = Password(data.at(0), password, categories.at(choice-1), data.at(1), data.at(2));
                passwordList.push_back(ps);
                passwordMap[categories.at(choice - 1)].push_back(ps);

                fmt::print(util::white, "\nPassword was created successfully. Here is overview\n");
                fmt::print(util::white, "{}\n", ps.to_string());

            }

        }
            break;

        default:
            fmt::print(util::white, "Invalid choice. In addPassword() option : {}\n", option);
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
    if (passwordList.size() == 0) { return false; }

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
    std::cin.ignore();
    login = inputType("login");
    std::cin.ignore();
    website = inputType("website");
    std::cin.ignore();

    return {name, website, login};
}

std::string inputType(const std::string type) {
    fmt::print(util::white, "\nGive me {} for password:\n\n> ", type);
    std::string attribute;
    std::cin >> attribute;

    // while work as long as  attr = - or atr<2 or is bad, if first 2 are false, last will work
    while (attribute == "-" || attribute.length() < 2 || isNotInSet(attribute) ) {
        fmt::print(util::error, util::Fault, type);
        std::cin >> attribute;
    }
    
    return attribute;
}

bool isPasswordPopular(const std::string& password) {
    std::string line;
    auto stream = std::fstream("rockyou.txt");
    bool popular = false;

    while (getline(stream, line)) {
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
    if (getAllCategories().size() < 1) { fmt::print(util::error, "\n0 categories withing a class\n"); return; }
    for (auto el : this->getAllCategories() ) {
        std::cout << el << std::endl;
    }
}

void PasswordPass::showPasswords() {
    if (passwordList.empty()) { fmt::print(util::error, "Password List Is Empty."); return; }
    int i = 1;
    for (auto& el : this->getPasswordList()) {
        fmt::print(util::white, "{} {}\n",i++, el.to_string());
    }
}

PasswordPass* PasswordPass::createAccount() {
    fmt::print(util::white, "\nYou`re in process of creating an account for Password managing\n");
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

void setOthers(const std::vector<std::string> vec, PasswordPass* ps) {
    ps->setOther(vec);
}

/*
* @brief setter for passwordList
*/
void setPassList(const std::vector<std::string> dirt, const char delimite, PasswordPass* ps) {
    ps->setPasswordList(passwordList(dirt, delimite));
}

PasswordPass* PasswordPass::loginIntoAccount() {
    fmt::print(util::white,"\nWould you like to pick a file from current folder or give a path? [F/P]\n\n> ");
    char input = inputAnswer('F', 'P', false);
    std::string path;
    if (input == 'P') {
        return PasswordPass::loginWithPath("");
    }

    return PasswordPass::loginFromFolder();
}

PasswordPass* PasswordPass::loginFromFolder() {
    if (!secretFolderIS()) {
        char answer;
        fmt::print(util::white,"\nThere is no Folder with secrets\nWould You like to create one or login with path? [C/P]\n> ");
        answer = inputAnswer('C', 'P', false);

        if (answer == 'P') {
            return PasswordPass::loginWithPath("");
        }
        
        if (std::filesystem::create_directory(util::secretFolder)) {
            fmt::print(util::white, "\nDirectory created successfully.\n");
            return PasswordPass::createAccount();
        }
        else {
            fmt::print(util::white, "\nFailed to create directory.\n");
            return nullptr;
        }
    }

    std::vector<std::string> currentOptions = allSecrets();
    if (currentOptions.size() < 1) { 
        fmt::print(util::error, "\nThere is no files in secret Folder\n"); 
    }

    fmt::print(util::white, "\nPlease choose one file from this list.\n");
    showList(currentOptions);
    
    int option = rangeAnswer(1, currentOptions.size());

    std::filesystem::path pathToFile = util::secretFolder;
    pathToFile.append(currentOptions.at(option-1));

    return PasswordPass::loginWithPath(pathToFile.string());
}

PasswordPass* PasswordPass::loginWithPath(const std::string autoPath) {
    std::string path;

    if (autoPath.empty()) {
        fmt::print(util::white, "\nPlease provide me with a path to a file\n\n> ");
        std::cin >> path;
        if (!std::filesystem::is_regular_file(path)) {
            path = correctPath(path);
        }
    }
    else {
        path = autoPath;
    }
    

    std::string password;
    fmt::print(util::white, "\nPlease provide me with a password to a file\n\n> ");
    std::cin >> password;

    bool dec = isDecrypted(path, password);

    if (!dec) {
        password = correctPassword(path);
    }

    std::vector<std::string> decipheredList = decryptFile(path, password);

    std::vector<std::string> others = filter(decipheredList);

    PasswordPass* ppass = new PasswordPass(path, password);
    
    setPassList(decipheredList, '|', ppass);
    

    ppass->populatePasswordMap();

    fmt::print(util::white, "\n\n\n\n\n\nLoged successfully pleasant use\n");

    if (others.size() == 4) { fmt::print(util::white, "\nLast login was {} may, {}:{}:{}\n", others.at(0), others.at(1), others.at(2), others.at(3)); }

    // day hour minute seconds
    std::vector<std::string> t = time();
    setOthers(t, ppass);

    return ppass;
}

PasswordPass* launch() {
    fmt::print(util::white, "\tHello to PPass aka PasswordPass\nWhould you like to login or create secret file?\n[L/C]\n\n> ");
    char input = inputAnswer('L', 'C', false);
    if (input == 'L') { 
        return PasswordPass::loginIntoAccount(); 
    }
    PasswordPass::createAccount();
    return nullptr;

}

PasswordPass::~PasswordPass() {
    delete &passwordList;
    delete &passwordMap;
}