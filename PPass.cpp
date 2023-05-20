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

void placeMainFolder();

void findPassword();

void sortPasswords();

void changePassword();

void removeDirectory();

void addCategory();

void recordDecryption();
    
void isPasswordSafe();

void createPassword();

/*
bool containsSpecialCharacters(const std::string& str) {
    std::regex pattern("\\\\(?![\\\"]|[nt])"); // all bad char for my code
    return std::regex_search(str, pattern);
}
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

void wrtieTimestamp(std::string filename) {
    // require a vector of dechipered lines or vector of empty lines where i can change smth and than change those lines
    std::vector<int> currTime = time();

}
*/
/*
struktura
"Hasło 1 na Google","password1","Internet","www.google.com","user1"
then split i dodaje sobie do Password
*/

/*
std::vector<std::string> split(const std::string& s, char delimiter) {

    std::vector<std::string> tokens;

    std::istringstream iss(s);

    std::string token;

    while (std::getline(iss, token, delimiter)) {
        tokens.push_back(token);
    }

    return tokens;
}


bool isDecrypted(std::string path, std::string password) {

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
*/

/*
pytanie jeszcze otwarte czy zostawiam pole kategoriew klasie haslom czy robie inna klase dla tego 
*/
//class Category {
//
//};
//
//class Password {
//private:
//	std::string name;
//	std::string text;
//	std::string category;
//	std::string website;
//	std::string login;
//	
//protected:
//	Password(std::string name, std::string text, std::string category, std::string website, std::string login) : 
//		name(name), text(text), category(category), website(website), login(login) {};
//	Password(std::string name, std::string text, std::string category) :
//		name(name), text(text), category(category), website(""), login("") {};
//};

//unfinished
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

/*
//Transfered
std::string correctPassword(std::string path, std::string errorMessage) {
    std::string password;
    do {
        fmt::print(fmt::fg(fmt::color::medium_violet_red), errorMessage);
        std::cin >> password;
    } while (!isDecrypted(path, password));

    return password;
}

//Transfered
std::string correctPath(std::string errorMessage) {
    std::string path;
    do {
        fmt::print(fmt::fg(fmt::color::medium_violet_red), errorMessage);
        std::cin >> path;
    } while (!std::filesystem::is_regular_file(path));
    //fmt::print(fmt::fg(fmt::color::green), "Great here you go with this path  {}", path+"\n");
    return path;
}

//Transfered
char inputAnswer(std::string errorMessage, char optionOne, char optionTwo) {
    char input = ' ';
    while (input != optionOne && input != optionTwo) {
        fmt::print(fmt::fg(fmt::color::medium_violet_red), errorMessage, optionOne, optionTwo);
        std::cin >> input;
    }
    return input;
}

*/

//in order to have static construcors i do this shaet
void setPassList(const std::vector<std::string> dirt, const char delimite, PasswordPass ps) {
    ps.setPasswordList(passwordList(dirt, delimite));
}

PasswordPass PasswordPass::loginIntoAccount() {
    fmt::print("Would you like to pick a file from current folder or give a path? [F/P]\n> ");
    std::string errorMessage = "Please type [{0}/{1}] not any other character [{0}/{1}]\n> ";
    char input; 
    std::cin >> input;
    std::string path;
    if (input != 'F' && input != 'P') {input = inputAnswer(errorMessage, 'F', 'P');}
    if (input == 'P') {
        fmt::print("Please provide me with a path to a file\n");
        std::cin >> path;
        if (!std::filesystem::is_regular_file(path)) {
            std::string errorMessage = "Please provide me with a correct path to a file\n";
            path = correctPath(errorMessage);
        }

        std::string password;
        fmt::print("Please provide me with a password to a file\n");
        std::cin >> password;

        bool dec = isDecrypted(path, password);

        if (!dec) {
            std::string errMsg = "Please provide correct password unless you want to disintegrate your file\n";
            password = correctPassword(path, errMsg);
        }
        //fmt::print("BEFORE\n");

        std::vector<std::string> decipheredList = decryptFile(path, password);

        /*for (auto el : decipheredList) {
            fmt::print("{}\n", el);
            
        }*/
        //std::string smth;
        std::vector<std::string> others = filter(decipheredList);

        //fmt::print("AFTER\n");
        /*for (auto el : decipheredList) {
            fmt::print("{}\n", el);
            
        }*/
        /*fmt::print("AND\n");
        for (auto el : others) {
            fmt::print("{}\n", el);

        }*/      
        PasswordPass ppass = PasswordPass(path, others);
        fmt::print("path to a file {}\n", ppass.getPathToFile());

        fmt::print("before setting\n");
        //setPassList(decipheredList, '|', ppass);
        fmt::print("after setting\n");
        return ppass;
        

    }
    std::vector<std::string> other;
    return PasswordPass(path, other);
}
    

PasswordPass PasswordPass::launch() {
    fmt::print(  fmt::fg(fmt::color::snow), "\tHello to PPass aka PasswordPass\nWhould you like to login or create secret file?\n[L/C]\n> ");
    std::string errorMessage = "Pleas type [{0}/{1}] not any other character\n[{0}/{1}]\n> ";
    char input;
    std::cin >> input;
    if (input != 'L' && input != 'C') { input = inputAnswer(errorMessage, 'L', 'C'); }
    if (input == 'L') { 
        return PasswordPass::loginIntoAccount(); 
    }
    return  PasswordPass::loginIntoAccount();
}

PasswordPass::~PasswordPass() {
    // Destructor implementation
    delete this;
}

//class PasswordPass {
//protected:
//	/**
//	* @homeFolder - path to a foldere where secret file is stored, or where to create new passwords
//	* @directFile - path to a direct file where to take data
//	*/
//	std::string homeFolder;
//	std::string directFile;
//	bool decyphired;
//	std::map<std::string, std::vector<Password>> passList;
//
//private:
//	PasswordPass(std::string homeFolder, std::string directFile) : homeFolder(homeFolder), directFile(directFile) {};
//	
//
//public:
//	static PasswordPass createAccount(std::string path_str) {
//		std::cout << "Wprowadｿ sczieｿke do pliku lub folderu z plikami szyfrowanymi\n: ";
//		std::string path_str;
//		cin >> path_str;
//		std::filesystem::path path_obj(path_str);
//
//		if (std::filesystem::is_directory(path_obj)) {
//			std::cout << "The path is a directory." << std::endl;
//			return PasswordPass(path_str, "");
//		}
//		else if (std::filesystem::is_regular_file(path_obj)) {
//			std::cout << "The path is a regular file." << std::endl;
//			return PasswordPass("", path_str);
//		}
//		else {
//			std::cout << "The path does not exist, Please make sure that given path is correct" << std::endl;
//			return PasswordPass("", "");
//		}
//	}
//};

//auto filename = "secret.txt";
//auto key = "password";
//
//auto stream = fstream(
//    filename
//);
//std::string line;
//vector<string> vec;
//while (stream >> line) {
//    vec.push_back(line);
//}
//vector<string> encrypted;
//
//for (auto el : vec) {
//    if (el.at(0) == '~' && el.at(el.length() - 1) == '~')
//    {
//        auto element = el.substr(1, el.length() - 2);
//        string ciphertext = '~' + encryptXOR(element, key) + '~';
//        encrypted.push_back(ciphertext);
//        cout << ciphertext << " ";
//    }
//}
//
//cout << endl << "CFUCKIGN CLEAR TEXT" << endl;
//
//for (auto el : encrypted) {
//    if (el.at(0) == '~' && el.at(el.length() - 1) == '~')
//    {
//        auto element = el.substr(1, el.length() - 2);
//        string clear = '~' + decryptXOR(element, key) + '~';
//        cout << clear << " ";
//    }
//}



