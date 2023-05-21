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
#include <cctype>
#include <algorithm>


namespace util {
    const fmt::text_style white = fmt::fg(fmt::color::snow);
    const fmt::text_style error = fmt::fg(fmt::color::medium_violet_red);
    const std::string pFault = "Provided password was not correct\n";
    const std::string wrongOption = "Please type [{0}/{1}] not any other character [{0}/{1}]\n> ";
    const std::string wrongRange = "Please type numbe in a range [{0}-{1}] not any other number [{0}-{1}]\n> ";
    const std::string errorPath = "Provided path: '{}' is not a correct path to a file\n";
    const std::string errorPass = "Please provide correct password unless you want to disintegrate your file\n";
    const std::filesystem::path home = std::filesystem::current_path();
    const std::filesystem::path homeParent = home.parent_path();
    const std::filesystem::path secretFolder = home.parent_path().append("secret");

}

int rangeAnswer(int min, int max) {
    int option;
    if (min <= 0) {
        min = 1;
    }
    std::cin >> option;
    while (!(option >= min && option <= max)) {
        fmt::print(util::error, util::wrongRange, min, max);
        std::cin >> option;
    }
    return option;
}

void showFiles(const std::vector<std::string>& files) {
    int pos = 1;

    for (const auto el : files) {
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

char inputAnswer(const  char optionOne, const char optionTwo) {
    char input = ' ';
    while (input != optionOne && input != optionTwo) {
        fmt::print(util::error, util::wrongOption, optionOne, optionTwo);
        std::cin >> input;
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
// w inszomu misci de vywolam paswordlist tam maju oczustutu stringa wid wsyakoi hyjni