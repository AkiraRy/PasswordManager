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
    //custom colors
    const std::vector<fmt::text_style> colors = {
        fmt::fg(fmt::color::coral),
        fmt::fg(fmt::color::alice_blue),
        fmt::fg(fmt::color::aquamarine),
        fmt::fg(fmt::color::dark_orchid),
        fmt::fg(fmt::color::deep_sky_blue),
        fmt::fg(fmt::color::lemon_chiffon),
        fmt::fg(fmt::color::steel_blue),
    };
    const std::vector<std::string> colorsString = {
        "coral",
        "alice_blue",
        "aquamarine",
        "dark_orchid",
        "deep_sky_blue",
        "lemon_chiffon",
        "steel_blue",
    };
    // default ones
    const fmt::text_style white = fmt::fg(fmt::color::snow);
    const fmt::text_style error = fmt::fg(fmt::color::pale_violet_red);
    fmt::text_style userColor = white;





    //sets for password fields
    const std::string capSet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const std::string lowSet = "abcdefghijklmnopqrstuvwxyz";
    const std::string numSet = "0123456789";
    const std::string symSet = "!@#$%^&*()_+-=[]{}|;:\",<.>/? ";

    // communication
    const std::string pFault = "\nProvided password was not correct\n";
    const std::string Fault = "\nProvided {} was not correct\n> ";
    const std::string cFault = "\nProvided category was not correct\n\n> ";
    const std::string wrongOption = "\nPlease type [{0}/{1}] not any other character [{0}/{1}]\n> ";
    const std::string wrongRange = "\nPlease type numbe in a range [{0}-{1}] not any other number [{0}-{1}]\n";
    const std::string errorPath = "\nProvided path: '{}' is not a correct path to a file\n\n> ";
    const std::string errorPass = "\nPlease provide correct password unless you want to disintegrate your file\n\n> ";
    const std::string errorFile = "\nProvided file is incorrect\n\n>";
    const std::filesystem::path home = std::filesystem::current_path();
    const std::filesystem::path homeParent = home.parent_path();
    const std::filesystem::path secretFolder = home.parent_path().append("secret");

    void setUserColor(const fmt::text_style& color) {
        userColor = color;
    }

    //menus
    void mainMenu() {
        fmt::print(userColor, "\n\t\tWelcome To Main Menu, Choose One Of The Next Options\n");
        fmt::print(userColor, " 1 - search Passwords\n");
        fmt::print(userColor, " 2 - sort Passwords\n");
        fmt::print(userColor, " 3 - add Password\n");
        fmt::print(userColor, " 4 - edit Password\n");
        fmt::print(userColor, " 5 - delete Password(s)\n");
        fmt::print(userColor, " 6 - add category\n");
        fmt::print(userColor, " 7 - delete category\n");
        fmt::print(userColor, " 8 - show all categories\n");
        fmt::print(userColor, " 9 - master password\n");
        fmt::print(userColor, "10 - show all password\n");
        fmt::print(userColor, "11 - show other\n");
        fmt::print(userColor, "12 - show PATH to file\n");
        fmt::print(userColor, "13 - customize color(fg)\n");
        fmt::print(userColor, "\n0 - quit the app\n\n");
    }

    void searchMenu() {
        fmt::print(userColor, "\n\n\t\tYou Are In Search Menu, choose one of the next options\n");
        fmt::print(userColor, "1 - search by category\n");
        fmt::print(userColor, "2 - search by name\n")   ;
        fmt::print(userColor, "3 - search by login\n");
        fmt::print(userColor, "4 - search by website\n");
        fmt::print(userColor, "5 - search by all optiions\n");
        fmt::print(userColor, "0 - return to the main men\n\n");
    }

    void sortMenu() {
        fmt::print(userColor, "\n\t\tYou Are In Menu, choose one of the next options:\n");
        fmt::print(userColor, "1 - sort by category\n");
        fmt::print(userColor, "2 - sort by name\n");
        fmt::print(userColor, "3 - sort by website\n");
        fmt::print(userColor, "4 - sort by login\n");
        fmt::print(userColor, "5 - sort by category and name\n");
        fmt::print(userColor, "0 - return to the main app\n\n");
    }

    void addPasswordMenu() {
        fmt::print(userColor, "\n\t\tYou Are In Add Password Menu, choose one of the next options:\n");
        fmt::print(userColor, "\nFollow The Rules, If You Dont Want to mentioned a field place '-'\n");
        fmt::print(userColor, "1 - create your own\n");
        fmt::print(userColor, "2 - generate\n");
        fmt::print(userColor, "0 - return to the main app\n\n");
    }

    void addCategoryMenu() {
        fmt::print(userColor, "\n\t\tYou Are In Add Category Menu, choose one of the next options:\n");
        fmt::print(userColor, "1 - proceed\n");
        fmt::print(userColor, "0 - return to the main app\n\n");
    }

    void deleteCategoryMenu() {
        fmt::print(userColor, "\n\t\tYou Are In Delete Category Menu, choose one of the next options:\n");
        fmt::print(userColor, "1 - proceed\n");
        fmt::print(userColor, "0 - return to the main app\n\n");
    }

    void editPasswordMenu() {
        fmt::print(userColor, "\n\t\tYou Are In Edit Password Menu, choose one of the next options:\n");
        fmt::print(userColor, "\nChoose on how to find password to edit\n");
        fmt::print(userColor, "1 - show all current passwords\n"); // tu dokonczyc zeby moc wprowadzicz dane do wyszukiwania
        fmt::print(userColor, "2 - by name\n");
        fmt::print(userColor, "3 - by category and then name\n");
        fmt::print(userColor, "0 - return to the main app\n\n");
    }

    void editingMenu() {
        fmt::print(userColor, "\n\t\tYou Are In Edit Password Menu, choose one of the next options:\n");
        fmt::print(userColor, "\nChoose what field to edit\n");
        fmt::print(userColor, "1 - category\n");
        fmt::print(userColor, "2 - name\n");
        fmt::print(userColor, "3 - password\n");
        fmt::print(userColor, "4 - login\n");
        fmt::print(userColor, "5 - website\n");
        fmt::print(userColor, "0 - end editing\n\n");
    }

    void deletePasswordMenu() {
        fmt::print(userColor, "\n\t\tYou Are In Delete Password Menu, choose one of the next options:\n");
        fmt::print(userColor, "\nChoose on how to find password to delete\n");
        fmt::print(userColor, "1 - from list\n");
        fmt::print(userColor, "2 - by category\n");
        fmt::print(userColor, "3 - by name\n");
        fmt::print(userColor, "4 - by category and then name\n");
        fmt::print(userColor, "0 - return to the main app\n\n");
    }

}

std::string PasswordPass::presentCategory() {
    std::string category;

    bool exists = false;
    do {

        fmt::print(util::userColor, "\nProvide category to be delete\n> ");
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

        fmt::print(util::userColor, "\nProvide a name for a category: ");
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
        else if (isNotInSet(category)) {
            fmt::print(util::error, util::cFault);
        }
        else {
            exists = true;
        }
    } while (!exists);

    return category;
}

bool isNotInSet(const std::string & inputString) {
    bool isBad = false;

    for (auto el : inputString) {
        if (util::capSet.find(el) == std::string::npos &&
            util::lowSet.find(el) == std::string::npos &&
            util::numSet.find(el) == std::string::npos &&
            util::symSet.find(el) == std::string::npos) {
            isBad = true;
            break;
        }
    }
    return isBad;
}

int readNumber() {
    std::string input;
    int value = -1  ;
    bool number = false;

    while (!number) {
        fmt::print(util::userColor, "\n> ");
        std::cin >> input;

        try {
            value = std::stoi(input);
            break;
            
        }
        catch (const std::invalid_argument& ex) {
            fmt::print(util::error, "\nError invalid argument\n");
        }
        catch (const std::out_of_range& ex) {
            fmt::print(util::error, "\nError: out of range\n");
        }

    }


    return value;

}

int random(const int min, int max) {
    if (min == max) { max++; }
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(min, max);
    return distribution(gen);
}

std::string generateRandomPassword(const int length,const bool includeUppercase,const bool includeSpecialChars) {
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

int rangeAnswer(int min,const int max) {


    if (min < 0) {
        min = 1;
    }
    bool first = true;
    int value = -1;

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

//here
void showList(const std::vector<std::string>& list) {
    int pos = 1;
    fmt::print("\n");
    for (const auto el : list) {
        fmt::print(util::userColor, "{} - {}\n", pos++, el);
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

std::vector<std::string> time() {
    std::time_t currentTime = std::time(nullptr);
    std::tm localTime{};
    localtime_s(&localTime, &currentTime);

    int hours = localTime.tm_hour;
    int minutes = localTime.tm_min;
    int seconds = localTime.tm_sec;
    int day = localTime.tm_mday;


    std::vector<std::string> timeList = { std::to_string(day), std::to_string(hours), std::to_string(minutes), std::to_string(seconds) };
    return timeList;
}

void writeTimestamp(const std::string& filename) {
    //reading
    std::vector<std::string> t = time();

    std::vector<std::string> data;

    std::string line;
    auto stream = std::fstream(filename, std::ios::in);
    if (!stream.is_open()) { fmt::print(util::error, util::errorFile); return; }
    while (getline(stream, line)) {
        if (isdigit(line.at(0))) {
            continue;
        }
        data.push_back(line);
    }
    stream.close();

    //randomizing write
    int i = 0;
    for (auto el : t) {
        int minToInsert = (int)(i * ((data.size() - 1) / 4)); // 0 1/3 2/3

        int maxToInsert = (int)((i + 1) * ((data.size() - 1) / 4)); // 1/3 2/3 3 
        if (minToInsert < 1) { minToInsert = 1; }
        if (minToInsert == maxToInsert) { maxToInsert++; }
        int indexToInsert = random(minToInsert, maxToInsert);
        data.insert(data.begin() + indexToInsert, t.at(t.size() - i - 1));
        i++;
        if (i == 4) { break; }
    }

    //write to file timestamp
    std::fstream outputFile; 
    outputFile.open(filename, std::ios::out);
    if (outputFile.is_open()) {
        for (const auto& el : data) {
            outputFile << el << "\n";
        }

        outputFile.close();
    }
    else {
        fmt::print(util::error, "\nError opening the file.\n");
    }


}

std::vector<std::string> split(const std::string& s, char delimiter) {

    std::vector<std::string> tokens;

    std::istringstream iss(s);

    std::string token;

    while (std::getline(iss, token, delimiter)) {// reads info until #delimiter is met
        tokens.push_back(token);
    }

    return tokens;
}

bool isDecrypted(const std::string &path, const std::string &password) {

    auto stream = std::fstream(path);
    if (!stream.is_open()) {
        fmt::print(util::error, util::errorFile);
        return false;
    }
    std::string beggining;
    getline(stream, beggining);
    if (beggining.empty()) { fmt::print(util::error, "File is empty"); return false; }
    if (decryptCaeser(beggining, password) == "DECRYPTED") {
        return true;
    }
    stream.close();
    return false;
}

std::string correctPassword(const std::string &path) {
    std::string password;
    do {
        writeTimestamp(path);

        fmt::print(util::error, util::errorPass);
        std::cin >> password;
        std::cin.clear();
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

char inputAnswer(const char optionOne, const char optionTwo, bool error) {
    bool first = true;

    std::string input = "  ";
    while ((input.at(0) != optionOne && input.at(0) != optionTwo ) || input.size() > 1) {
        if (first && !error) {
            std::cin >> input;
            first = false;
        }
        
        else {
            fmt::print(util::error, util::wrongOption, optionOne, optionTwo);
            std::cin >> input;
        }
    }
    return input.at(0);
}

std::vector<Password> passwordList(const std::vector<std::string> &dirt,const  char delimite) {
    std::vector<Password> pList ;
    if (dirt.empty()) { return pList; }
    for (auto el : dirt) {
        if (el.length() > 0) { // jezeli to NIE linia pusta
            if (el.at(0) == 'd') { // password start
                el.erase(0, 1);
                std::vector<std::string> str = split(el, '|');
                if (str.size() != 5) { fmt::print(util::error, "Provided password was not correct\n"); continue; }

                Password ps = Password(str.at(0), str.at(1), str.at(2), str.at(3), str.at(4));

                pList.push_back(ps);

            }
            
        }

    }

    return pList;
}

/// <summary>
/// filteres a vector from info that do not contain passwords, and stores it in another vector
/// </summary>
/// <param name="unfiltered">decrypted vector of lines from file</param>
/// <returns>vector of lines that do not contain password info</returns>
std::vector<std::string> filter(std::vector<std::string>& unfiltered) {
    std::vector<std::string> other;

    auto partitionPoint = std::partition(unfiltered.begin(), unfiltered.end(), [](const std::string& line) {
        return line.length() > 0 && line[0] == 'd';
        });

    std::move(partitionPoint, unfiltered.end(), std::back_inserter(other));


    unfiltered.erase(partitionPoint, unfiltered.end());


    return other;
}