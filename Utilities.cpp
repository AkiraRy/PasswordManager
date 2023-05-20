#define FMT_HEADER_ONLY
#include "Utilities.h"
#include "Decryption.h"
#include "Encryption.h"
#include "Password.h"
#include <regex>
#include <string>
#include <vector>
#include <iostream>
#include <ctime>
#include <fstream>
#include <fmt/core.h>
#include <fmt/color.h>
#include <filesystem>

bool containsSpecialCharacters(const std::string& str) {
    std::regex pattern("\\\\(?![\\\"]|[nt])"); // all bad char for my code
    return std::regex_search(str, pattern);
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
        fmt::print(fmt::fg(fmt::color::medium_violet_red), "Error opening file: \n");
        return false;
    }
    std::string beggining;
    getline(stream, beggining);
    if (decryptCaeser(beggining, password) == "DECRYPTED") {
        return true;
    }
    return false;
}

std::string correctPassword(const std::string path,const std::string errorMessage) {
    std::string password;
    do {
        fmt::print(fmt::fg(fmt::color::medium_violet_red), errorMessage);
        std::cin >> password;
    } while (!isDecrypted(path, password));

    return password;
}

std::string correctPath(const std::string errorMessage) {
    std::string path;
    do {
        fmt::print(fmt::fg(fmt::color::medium_violet_red), errorMessage);
        std::cin >> path;
    } while (!std::filesystem::is_regular_file(path));
    //fmt::print(fmt::fg(fmt::color::green), "Great here you go with this path  {}", path+"\n");
    return path;
}

char inputAnswer(const std::string errorMessage, const  char optionOne, const char optionTwo) {
    char input = ' ';
    while (input != optionOne && input != optionTwo) {
        fmt::print(fmt::fg(fmt::color::medium_violet_red), errorMessage, optionOne, optionTwo);
        std::cin >> input;
    }
    return input;
}


std::vector<Password> passwordList(const std::vector<std::string> dirt,const  char delimite) {
    std::vector<Password> ps;



    return ps;
}