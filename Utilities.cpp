#define FMT_HEADER_ONLY
#include "Utilities.h"
#include "Decryption.h"
#include "Encryption.h"
#include "Password.h"
#include "PPass.h"
#include <regex>
#include <string>
#include <vector>
#include <iostream>
#include <ctime>
#include <fstream>
#include <fmt/core.h>
#include <fmt/color.h>
#include <filesystem>
#include <cctype>
#include <algorithm>
#include <random>

namespace util {
    const fmt::text_style white = fmt::fg(fmt::color::snow);
    const fmt::text_style error = fmt::fg(fmt::color::pale_violet_red);
    const std::string pFault = "\nProvided password was not correct\n";
    const std::string Fault = "\nProvided {} was not correct\n";
    const std::string cFault = "\nProvided category was not correct\n";
    const std::string wrongOption = "\nPlease type [{0}/{1}] not any other character [{0}/{1}]\n> ";
    const std::string wrongRange = "\nPlease type numbe in a range [{0}-{1}] not any other number [{0}-{1}]\n> ";
    const std::string errorPath = "\nProvided path: '{}' is not a correct path to a file\n";
    const std::string errorPass = "\nPlease provide correct password unless you want to disintegrate your file\n";
    const std::filesystem::path home = std::filesystem::current_path();
    const std::filesystem::path homeParent = home.parent_path();
    const std::filesystem::path secretFolder = home.parent_path().append("secret");


    void mainMenu() {
        fmt::print(white, "\n\t\tWelcome To Main Menu, Choose One Of The Next Options\n");
        fmt::print(white, "1 - search Passwords\n");
        fmt::print(white, "2 - sort Passwords\n");
        fmt::print(white, "3 - add Password\n");
        fmt::print(white, "4 - edit Password\n");
        fmt::print(white, "5 - delete Password(s)\n");
        fmt::print(white, "6 - add category\n");
        fmt::print(white, "7 - delete category\n");
        fmt::print(white, "0 - quit the app\n\n");
    }

    void searchMenu() {
        fmt::print(white, "\n\n\t\tYou Are In Search Menu, choose one of the next options\n");
        fmt::print(white, "1 - search by category\n");
        fmt::print(white, "2 - search by name\n")   ;
        fmt::print(white, "3 - search by login\n");
        fmt::print(white, "4 - search by website\n");
        fmt::print(white, "5 - search by all optiions\n");
        fmt::print(white, "0 - return to the main men\n\n");
    }

    void sortMenu() {
        fmt::print(white, "\n\t\tYou Are In Menu, choose one of the next options:\n");
        fmt::print(white, "1 - sort by category\n");
        fmt::print(white, "2 - sort by name\n");
        fmt::print(white, "3 - sort by website\n");
        fmt::print(white, "4 - sort by login\n");
        fmt::print(white, "5 - sort by more than 1 option\n");
        fmt::print(white, "0 - return to the main app\n\n");
    }

    void addPasswordMenu() {
        fmt::print(white, "\n\t\tYou Are In Add Password Menu, choose one of the next options:\n");
        fmt::print(white, "\nFollow The Rules, If You Dont Want to mentioned a field place '-'\n");
        fmt::print(white, "1 - create your own\n");
        fmt::print(white, "2 - generate\n");
        fmt::print(white, "0 - return to the main app\n\n");
    }

    void addCategoryMenu() {
        fmt::print(white, "\n\t\tYou Are In Add Category Menu, choose one of the next options:\n");
        fmt::print(white, "1 - proceed\n");
        fmt::print(white, "0 - return to the main app\n\n");
    }

    void deleteCategoryMenu() {
        fmt::print(white, "\n\t\tYou Are In Delete Category Menu, choose one of the next options:\n");
        fmt::print(white, "1 - proceed\n");
        fmt::print(white, "0 - return to the main app\n\n");
    }

    void editPasswordMenu() {
        fmt::print(white, "\n\t\tYou Are In Edit Password Menu, choose one of the next options:\n");
        fmt::print(white, "\nChoose on how to find password to edit\n");
        fmt::print(white, "1 - by category\n");
        fmt::print(white, "2 - by name\n");
        fmt::print(white, "3 - by category and then name\n");
        fmt::print(white, "0 - return to the main app\n\n");
    }

    void editingMenu() {
        fmt::print(white, "\n\t\tYou Are In Edit Password Menu, choose one of the next options:\n");
        fmt::print(white, "\nChoose what field to edit\n");
        fmt::print(white, "1 - category\n");
        fmt::print(white, "2 - name\n");
        fmt::print(white, "3 - password\n");
        fmt::print(white, "4 - login\n");
        fmt::print(white, "5 - website\n");
        fmt::print(white, "0 - end editing\n\n");
    }

    void deletePasswordMenu() {
        fmt::print(white, "\n\t\tYou Are In Delit Password Menu, choose one of the next options:\n");
        fmt::print(white, "\nChoose on how to find password to delete\n");
        fmt::print(white, "1 - by category\n");
        fmt::print(white, "2 - by name\n");
        fmt::print(white, "3 - by category and then name\n");
        fmt::print(white, "0 - return to the main app\n\n");
    }

}

std::string PasswordPass::presentCategory() {
    std::string category;

    bool exists = false;
    do {

        fmt::print(util::white, "\nProvide category to be delete\n> ");
        std::cin >> category;

        for (const auto& el : getAllCategories()) {
            if (el == category) {
                exists = true;
                break;
            }
        }

        if (!exists) {
            fmt::print(util::error, "\nCategory '{}' doesn`t exists. Please choose a different category.\n", category);
        }
    } while (!exists);

    return category;
}

std::string PasswordPass::uniqueCategory() {
    std::string category;

    bool exists;
    do {
        exists = false;

        fmt::print(util::white, "\nProvide a name for a category: ");
        std::cin >> category;

        for (const auto& el : getAllCategories()) {
            if (el == category) {
                exists = true;
                break;
            }
        }

        if (exists) {
            fmt::print(util::error, "\nCategory '{}' already exists. Please choose a different name.\n", category);
        }
    } while (!exists);

    return category;
}

int readNumber() {
    std::string input;
    int value = -1  ;
    bool number = false;

    while (!number) {
        std::cin >> input;

        try {
            value = std::stoi(input);
            break;
            
        }
        catch (const std::invalid_argument& ex) {
            fmt::print(util::error, "\nError invcalid argument\n");
        }
        catch (const std::out_of_range& ex) {
            fmt::print(util::error, "\nError: out of range\n");
        }

    }


    return value;

}

std::string generateRandomPassword(int length, bool includeUppercase, bool includeSpecialChars) {
    const std::string capSet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const std::string lowSet = "abcdefghijklmnopqrstuvwxyz";
    const std::string numSet = "0123456789";
    const std::string symSet = "!@#$%^&*()_+-=[]{}|;:\",<.>/? ";

    std::string charset;
    //default
    charset += lowSet;
    if (includeUppercase)
        charset += capSet;
    if (includeSpecialChars)
        charset += symSet;
    charset += numSet;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(charset.begin(), charset.end(), gen);

    std::string password;
    for (int i = 0; i < length; ++i) {
        password += charset[gen() % charset.length()];
    }

    return password;
}


int rangeAnswer(int min, int max) {


    if (min < 0) {
        min = 1;
    }
    bool first = true;;
    int value;

    do {
        if (first) {
            value = readNumber();
            first = false;
        }
        else {
            fmt::print(util::error, util::wrongRange, min, max);
            value = readNumber();
        }

    } while (!(value >= min && value <= max));
        
    
    return value;
}

void showList(const std::vector<std::string>& list) {
    int pos = 1;

    for (const auto el : list) {
        fmt::print(util::white, "{} - {}\n", pos++, el);
    }
}

std::vector<std::string> allSecrets() {
    auto dir_it = std::filesystem::directory_iterator(util::secretFolder);
    
    std::vector<std::string> secretFiles;


    for (auto element : dir_it) {
        if (element.path().extension() == ".txt") {
            secretFiles.push_back(element.path().filename().string());
        }
    }
    return secretFiles;
}

bool containsSpecialCharacters(const std::string& str) {
    std::regex pattern("\\\\(?![\\\"]|[nt])"); // all bad char for my code
    return std::regex_search(str, pattern);
}

bool secretFolderIS() {

    auto dir_it = std::filesystem::directory_iterator(util::homeParent);

    bool presented = false;

    for (auto element : dir_it) {
        if (element.path().filename() == "secret") {
            presented = true;
        }
    }
    return presented;
}

//done
std::vector<int> time() {
    std::time_t currentTime = std::time(nullptr);
    std::tm localTime{};
    localtime_s(&localTime, &currentTime);

    int hours = localTime.tm_hour;
    int minutes = localTime.tm_min;
    int seconds = localTime.tm_sec;

    std::vector<int> timeList = { hours, minutes, seconds };
    return timeList;
}

//need to finish this
void wrtieTimestamp(const std::string filename) {
    // require a vector of dechipered lines or vector of empty lines where i can change smth and than change those lines
    std::vector<int> currTime = time();

}

std::vector<std::string> split(const std::string& s, char delimiter) {

    std::vector<std::string> tokens;

    std::istringstream iss(s);

    std::string token;

    while (std::getline(iss, token, delimiter)) {
        tokens.push_back(token);
    }

    return tokens;
}

bool isDecrypted(const std::string path, const std::string password) {

    auto stream = std::fstream(path);
    if (!stream.is_open()) {
        // Handle the error if the file couldn't be opened
        fmt::print(util::error, "Error opening file: \n");
        return false;
    }
    std::string beggining;
    getline(stream, beggining);
    if (decryptCaeser(beggining, password) == "DECRYPTED") {
        return true;
    }
    return false;
}

std::string correctPassword(const std::string path) {
    std::string password;
    do {
        fmt::print(util::error, util::errorPass);
        std::cin >> password;
    } while (!isDecrypted(path, password));

    return password;
}

std::string correctPath(const std::string previousPATH) {
    std::string path = previousPATH;
    do {
        fmt::print(util::error, util::errorPath, path);
        std::cin >> path;
    } while (!std::filesystem::is_regular_file(path));
    return path;
}

char inputAnswer(const  char optionOne, const char optionTwo, bool error) {
    bool first = true;

    char input = ' ';
    while (input != optionOne && input != optionTwo) {
        if (first && !error) {
            std::cin >> input;
            first = false;

        }
        else {
            fmt::print(util::error, util::wrongOption, optionOne, optionTwo);
            std::cin >> input;
        }
    }
    return input;
}

/// <summary>
/// Creates a vector with Password instances
/// </summary>
/// <param name="dirt">raw vector with lines from a file</param>
/// <param name="delimite"></param>
/// <returns>vector<Password></returns>
std::vector<Password> passwordList(const std::vector<std::string> dirt,const  char delimite) {
    std::vector<Password> pList;

    for (auto el : dirt) {
        if (el.length() > 0) { // jezeli to NIE linia pusta
            if (el.at(0) == 'd') { // 
                el.erase(0, 1);
                std::vector<std::string> str = split(el, '|');
                if (str.size() != 5) { fmt::print(util::error, "Provided password was not correct\n"); continue; }



                Password ps = Password(str.at(0), str.at(1), str.at(2), str.at(3), str.at(4));

                pList.push_back(ps);

            }
            else if (isdigit(el.at(0))) {

            }
        }

    }

    return pList;
}

/// <summary>
/// filteres a vector from info that do not contain passwords
/// </summary>
/// <param name="unfiltered"></param>
/// <returns>vector of lines that do not contain password info</returns>
std::vector<std::string> filter(std::vector<std::string>& unfiltered) {
    std::vector<std::string> other;

    auto partitionPoint = std::partition(unfiltered.begin(), unfiltered.end(), [](const std::string& line) {
        return line.length() > 0 && line[0] == 'd';
        });

    //back_inserter to efficiently move string and do not make copies of them
    std::move(partitionPoint, unfiltered.end(), std::back_inserter(other));


    unfiltered.erase(partitionPoint, unfiltered.end());


    return other;
}
