#pragma once
#include <regex>
#include <string>
#include <vector>
#include <ctime>
#include <fstream>
#include <fmt/core.h>
#include <fmt/color.h>
#include <filesystem>
#include "Password.h"


namespace util {
	extern const fmt::text_style white;
	extern const fmt::text_style error;
	extern const std::string wrongOption;
	extern const std::string wrongRange;
	extern const std::string errorPath;
	extern const std::string errorPass;
	extern const std::string pFault;
	extern const std::string Fault;
	extern const std::string cFault;
	extern const std::filesystem::path home;
	extern const std::filesystem::path homeParent;
	extern const std::filesystem::path secretFolder;

	void mainMenu();
	void searchMenu();
	void sortMenu();
	void addPasswordMenu();
	void editPasswordMenu();
	void deletePasswordMenu();
	void addCategoryMenu();
	void deleteCategoryMenu();
	void editingMenu();
}
int random(int min, int max);

int readNumber();

std::string generateRandomPassword(int length, bool includeUppercase,  bool includeSpecialChars);

int rangeAnswer(int min, int max);

void showList(const std::vector<std::string>& files);

std::vector<std::string> allSecrets();

/// \brief Checks if there is a foldeer with secret files
///
/// \param str - message
/// \returns bool
bool secretFolderIS();

/// \brief Checks if a string has special Characters 
///
/// \param str - message
/// \returns bool
bool containsSpecialCharacters(const std::string& str);

/// \brief current time
///
/// \returns hh mm ss current time in vector
std::vector<int> time();

void wrtieTimestamp(const std::string filename);

/// \brief Splits a string on provided delimiter
///
/// \param s - message
/// \param delimiter - character to divide string  
/// \returns splited vector<string> 
std::vector<std::string> split(const std::string& s,const char delimiter);

/// \brief Checks if file was decrypted successfully
///
/// \param path - path to a file
/// \param passsword - password to a file
/// \returns bool
bool isDecrypted(const std::string path, const  std::string password);

/// \brief Checks if provided password is correct for given file
///
/// \param path - path to a file
/// \param errorMessage - message to printout in case of wrong password
/// \returns correct password	
std::string correctPassword(const std::string path);

/// \brief Waits for correctPath to be provided
///
/// \param errorMessage - message to printout in case of wrong password
/// \returns correct path to a file
std::string correctPath(std::string previousPATH);

/// \brief Waits for correctPath to be provided
///
/// \returns correct path to a file
char inputAnswer( const char optionOne, const char optionTwo, bool error);

/// \brief Makes an list type of Password
///
/// \param dirt - unprepared list of passwords
/// \returns clear list of Passwords
std::vector<Password> passwordList(const std::vector<std::string> dirt, const  char delimite);

std::vector<std::string> filter(std::vector<std::string>& unfiltered);

//when pushing timestamp to a file divide it by 3, and by random for index in vector push it.