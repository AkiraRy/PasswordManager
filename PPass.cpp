#define FMT_HEADER_ONLY
#include "PPass.h"
#include "Decryption.h"
#include "Encryption.h"
#include <fmt/core.h>
#include <fmt/color.h>
#include <iostream>
#include <vector>
#include <map>
#include <filesystem>
#include <fstream>

using std::cin, std::cout, std::endl;


void placeMainFolder();

void findPassword();

void sortPasswords();

void changePassword();

void removeDirectory();

void addCategory();

void recordDecryption();

void isPasswordSafe();

void createPassword();

bool isDecrypted(std::string path, std::string password) {

    auto stream = std::fstream(path);
    if (!stream.is_open()) {
        // Handle the error if the file couldn't be opened
        std::cerr << "Error opening file: " << path << std::endl;
        return false;
    }
    std::string beggining;
    getline(stream, beggining);
    if (decryptCaeser(beggining, password) == "DECRYPTED") {
        return true;
    }
    return false;
}


class Password {
private:
	std::string name;
	std::string text;
	std::string category;
	std::string website;
	std::string login;
	
protected:
	Password(std::string name, std::string text, std::string category, std::string website, std::string login) : 
		name(name), text(text), category(category), website(website), login(login) {};
	Password(std::string name, std::string text, std::string category) :
		name(name), text(text), category(category), website(""), login("") {};
};

PasswordPass::PasswordPass(std::string homeFolder, std::string directFile) : homeFolder(homeFolder), directFile(directFile) {}

PasswordPass PasswordPass::createAccount() {
    std::string path_str;
    std::cout << "Wprowadż sczieżke do pliku lub folderu z plikami szyfrowanymi\n: ";
    cin >> path_str;
    std::filesystem::path path_obj(path_str);

    if (std::filesystem::is_directory(path_obj)) {
        std::cout << "The path is a directory." << std::endl;
        return PasswordPass(path_str, "");
    }
    else if (std::filesystem::is_regular_file(path_obj)) {
        std::cout << "The path is a regular file." << std::endl;
        return PasswordPass("", path_str);
    }
    else {
        std::cout << "The path does not exist, Please make sure that given path is correct" << std::endl;
        return PasswordPass("", "");
    }
}

std::string correctPath(std::string errorMessage) {
    std::string path;
    do {
        fmt::print(fmt::fg(fmt::color::medium_violet_red), errorMessage);
        std::cin >> path;
    } while (!std::filesystem::is_regular_file(path));
    fmt::print(fmt::fg(fmt::color::green), "Great here you go with this path  {}", path);
    return path;
}

char inputAnswer(std::string errorMessage, char optionOne, char optionTwo) {
    char input = ' ';
    while (input != optionOne && input != optionTwo) {
        fmt::print(fmt::fg(fmt::color::medium_violet_red), errorMessage, optionOne, optionTwo);
        std::cin >> input;
    }
    return input;
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
        cin >> password;

        bool dec = isDecrypted(path, password);
        if (dec) {
            fmt::print("yay");
        }
        else {
            fmt::print("fuck");
        }

    }
    return PasswordPass("", path);
}
    

PasswordPass PasswordPass::launch() {
    fmt::print(  fmt::fg(fmt::color::snow), "\tHello to PPass aka PasswordPass\nWhould you like to login or create secret file?\n[L/C]\n> ");
    std::string errorMessage = "Pleas type [{0}/{1}] not any other character\n[{0}/{1}]\n> ";
    char input;
    std::cin >> input;
    if (input != 'L' && input != 'C') { input = inputAnswer(errorMessage, 'L', 'C'); }
    if (input == 'L') { return PasswordPass::loginIntoAccount(); }
    return PasswordPass::createAccount();
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



//add first line to a file like {#DECRYPTED#} i czytasz 1 linije jezeli ta  lnia nie jest taka to walish gowno z komputera


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



